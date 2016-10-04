
#include "tm4c123gh6pm.h"
#include "ADC.h"

// Sample rate 125k samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller
// PE2 - AIN1
void ADC_Init(void)
{
	// Init PE2 as digital input
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // Port E clock
	delay = SYSCTL_RCGC2_R; 
	GPIO_PORTE_DIR_R &= ~0x04; // PE2 input
	GPIO_PORTE_DEN_R &= ~0x04; // PE2 digital disabled
	GPIO_PORTE_AMSEL_R |= 0x04; // PE2 -> AIN1 (analog mode)
	GPIO_PORTE_AFSEL_R |= 0x04; // PE2 -> AIN1 (alt.func.)
	
	// Turn ADC clock
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC0; // ADC0 clock
	delay = SYSCTL_RCGC0_R;
	// Configure sample speed
	SYSCTL_RCGC0_R &= ~ 0x300; // 125K samples/second (ADC0 Sample Speed)
	// Select sample sequencer priority
	ADC0_SSPRI_R &= 0x0123; //~0x3000; // SS3 is highest priority(0x0 highest, 0x3 lowest)
	// Select sample sequencer(and disable)
	ADC0_ACTSS_R &= ~0x08; // SS3 disabled for config
	// Trigger 
	ADC0_EMUX_R  &= ~0xF000; // SW Initiated
	// Choose channel
	ADC0_SSMUX3_R = 0x01; // AIN1-0001
	// SSI3 Control
	ADC0_SSCTL3_R = 0x06; // IE0, END0
	// Enable SSI3
	ADC0_ACTSS_R |= 0x08; // done
}

// Busy-wait
unsigned long ADC0_IN(void)
{
	unsigned long result;
	ADC0_PSSI_R |= 0x08; // begin sampling
	while((ADC0_RIS_R&0x08)==0); // Raw Interrupt Status(Check the flag)
	result = ADC0_SSFIFO3_R & 0xFFF; // read with 12-bit mask
	ADC0_ISC_R |= 0x08; // ack of adc
	return result;
}

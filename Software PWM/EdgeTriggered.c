#include "tm4c123gh6pm.h"
#include "PortF.h"


// PF4(SW1) and PF0(SW2) interrupt on falling edge
void EdgeInt_Init(void)
{
	PortF_Init(); // PF4&PF0 configured as digital input
	
	// Clear PMC bits to use edge-triggered interrupts.
	GPIO_PORTF_PCTL_R &= ~0x000F000F; 
	// Clear IS(Interrupt Sense) bit(for edge-sensitive)
	GPIO_PORTF_IS_R  &= ~0x11; 
	// Clear IBE(Interrupt Both Edge)
	GPIO_PORTF_IBE_R &= ~0x11; // Interrupt generation will be controlled by GPIOIEV
	// Clear IEV(Interrupt Event) 
	GPIO_PORTF_IEV_R &= ~0x11; // Falling edge triggers an interrupt.
	// Set IM(Interrupt Mask)
	GPIO_PORTF_IM_R |= 0x11; // The interrupt is sent to the interrupt controller.(arm interrupt)
	// Clear Flag
	GPIO_PORTF_ICR_R = 0x11;
	
	// Vector Number 46, Interrupt Number 30
	// Interrupt 0-31 Set Enable(EN0)
	// Interrupt 28-31 Priority(PRI7)
	// Bits 23:21 - Interrupt[4n+2]
	// 0 highest, 7 lowest
	NVIC_PRI7_R |= 0xA00000; // Priority 5
	NVIC_EN0_R = 0x4000000; // enable interrupt 30 in NVIC
	NVIC_EnableIRQ(GPIOF_IRQn); // enable interrupts
}


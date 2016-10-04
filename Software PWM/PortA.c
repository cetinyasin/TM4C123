#include "tm4c123gh6pm.h"
#include "PortA.h"

// PA5 output

void PortA_Init(void)
{
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // Port A Clock
	delay = SYSCTL_RCGC2_R;								// allow time
	GPIO_PORTA_AMSEL_R &= ~0x20; 			    // No analog funct.
	GPIO_PORTA_PCTL_R  &= ~0x00F00000;  	// regular funct.
	GPIO_PORTA_DIR_R   |=  0x20; 			    // PA5 output
	GPIO_PORTA_DR8R_R  |=  0x20;          // 8mA drive enabled
	GPIO_PORTA_AFSEL_R &= ~0x20; 				  // No alternative funct.
	GPIO_PORTA_DEN_R   |=  0x20;			    // PA5 digital enabled
}


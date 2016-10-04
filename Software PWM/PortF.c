#include "tm4c123gh6pm.h"
#include "PortF.h"
// PF4-PF0 [SW1-SW2] input;
// PF3,PF2,PF1 output

void PortF_Init(void)
{
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // Port F Clock
	delay = SYSCTL_RCGC2_R;								// allow time
	GPIO_PORTF_LOCK_R   =  0x4C4F434B; 		// Unlock PF0
	GPIO_PORTF_CR_R 		=  0x1F;      	  // allow changes to PF4-0   
	GPIO_PORTF_AFSEL_R &= ~0x1F; 				  // No alternative funct.
	GPIO_PORTF_AMSEL_R &= ~0x1F; 			    // No analog funct.
	GPIO_PORTF_DIR_R   |=  0x0E; 			    // PF3, PF2, PF1 output
	GPIO_PORTF_DIR_R   &= ~0x11; 			    // PF4, PF0 input
	GPIO_PORTF_DEN_R   |=  0x1F;			    // PF4 - PF0 digital enabled
	GPIO_PORTF_PCTL_R  &= ~0x1F; 			    // regular funct.
	GPIO_PORTF_PUR_R   |=  0x11;          // Pull-up resistors PF4, PF0
}



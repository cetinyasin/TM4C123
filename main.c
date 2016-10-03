
#include "tm4c123gh6pm.h"
#include "PortF.h"
#include "Delay.h"

// Red -> Blue -> Green with 0.2 sec delay and then
// If PF0(SW2) is pressed then led -> green,
// If PF4(SW1) is pressed then led -> red

/* ******TM4C123********/
// Color    LED(s) PortF
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

void RBG(void);

int main(void)
{
	PortF_Init(); 
	RBG();
	while(1)
	{
		if((GPIO_PORTF_DATA_R & 0x10) == 0) 	 // SW1 is pressed(negative logic)
			GPIO_PORTF_DATA_R = 0x0A; 	 // yellow
		else if((GPIO_PORTF_DATA_R & 0x01) == 0) // SW2 is pressed(negative logic)
			GPIO_PORTF_DATA_R = 0x0C; 	 // sky blue  
		else
			GPIO_PORTF_DATA_R = 0;
	}
}

void RBG(void)
{
	GPIO_PORTF_DATA_R = 0x02; // red
	Delay100ms(2); // 0.2sec 
	GPIO_PORTF_DATA_R = 0x04; // blue
	Delay100ms(2); // 0.2sec 
	GPIO_PORTF_DATA_R = 0x08; // green
	Delay100ms(2); // 0.2sec 
}

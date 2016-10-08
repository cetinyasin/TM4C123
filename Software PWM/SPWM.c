#include "tm4c123gh6pm.h"
#include "PortF.h"
#include "PortA.h"
#include "EdgeTriggered.h"
#include "SysTick.h"
#include "PLL.h"

/* Software PWM by using SysTick interrupts.
	SW1(PF4) speed up
	SW2(PF0) slow down
	PA5 Software PWM output */
	
// L range: 8000,16000,24000,32000,40000,48000,56000,64000,72000
// power:   10%    20%   30%   40%   50%   60%   70%   80%   90%
	
	
	unsigned long H=40000, L=40000; // 50%
int main(void) // SPWM
{
	PLL_Init(); // 80MHz
	PortA_Init(); // PA5 output
	SysTick_Init(L); // SysTick Timer Interrupts (H+L=80000; 80Mhz/80kHz=> 1ms period)
	EdgeInt_Init();  // PortF Init and Edge Interrupts Init
	while(1)
	{
	}
}

// ISR Routines
void SysTick_Handler(void)
{
	if(GPIO_PORTA_DATA_R&0x20) // if high now
	{
		GPIO_PORTA_DATA_R &= ~0x20; // PA5 low
		NVIC_ST_RELOAD_R = L-1;  // reload low value
	}
	else
	{
		GPIO_PORTA_DATA_R |= 0x20;  // PA5 high
		NVIC_ST_RELOAD_R = H-1;  // reload high value
	}
}

void GPIOF_Handler(void)
{
	if(GPIO_PORTF_RIS_R & 0x01) // SW2(PF0) interrupt
	{
		GPIO_PORTF_ICR_R = 0x01; // acknowledge PF0 flag
		if(L>8000) L -= 8000;
	}
	if(GPIO_PORTF_RIS_R & 0x10) // SW1(PF4) interrupt
	{
		GPIO_PORTF_ICR_R = 0x10; // acknowledge PF4 flag
		if(L<72000) L += 8000;
	}
	H = 80000-L; // constant period of 1ms, variable duty cycle
}


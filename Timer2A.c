#include "tm4c123gh6pm.h"
#include "Timer2A.h"


void Timer2A_Init(unsigned long period)
{
	// Page 722, One Shot/Periodic Timer Mode
	SYSCTL_RCGCTIMER_R |= 0x04; // Timer2
	TIMER2_CTL_R &= ~0x01;  // disable Timer2A during setup
	TIMER2_CFG_R = 0x00; // 32-bit mode
	TIMER2_TAMR_R = 0x02; // Periodic timer mode
	TIMER2_TAILR_R = period-1; // reload value
	TIMER2_TAPR_R = 0; // prescale (0: 1)
	TIMER2_ICR_R = 0x01; // TATOCINT, clear timer2A Time out interrupt
	TIMER2_IMR_R = 0x01; // TATOIM, Time-Out Int. Mask
	
	// Timer 2A vector number: 39, Interrupt number:23
	NVIC_PRI5_R |= 0x80000000; // pri 4
	NVIC_EN0_R = 1<<23; // IRQ
	
	TIMER2_CTL_R = 0x01; // Enable Timer2A.
}

void TIMER2A_Handler(void)
{
	TIMER2_ICR_R = TIMER_ICR_TATOCINT; // acknowledge 
	GPIO_PORTF_DATA_R ^= 0x02;
}
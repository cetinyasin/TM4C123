#include "tm4c123gh6pm.h"
#include "SysTick.h"

void SysTick_Init(unsigned long freq)
{
	NVIC_ST_CTRL_R = 0; // Disable for config.
	NVIC_ST_RELOAD_R = freq; // RELOAD 24-bit register (2^24=16.777.216)
	NVIC_ST_CURRENT_R = 0; // clear
	NVIC_SYS_PRI3_R |= 0x40000000; // priority 2
	NVIC_ST_CTRL_R = 0x07; // clk, int, enabled
}

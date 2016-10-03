#include "tm4c123gh6pm.h"
#include "PortF.h"

void SysTick_Init(unsigned long freq)
{
	NVIC_ST_CTRL_R = 0; // Disable for config.
	NVIC_ST_RELOAD_R = 16000000/freq; // RELOAD 24-bit register (2^24=16.777.216)
	NVIC_ST_CURRENT_R = 0; // clear
	NVIC_ST_CTRL_R = 0x07; // clk, int, enabled
}

unsigned long cnt;
void SysTick_Handler(void) // every 0.1 sec
{
	cnt++;
}

int main(void)
{
	PortF_Init();
	SysTick_Init(100);  // 100 Hz
	while(1)
	{
		if(cnt==100) // 1 sec
		{
			GPIO_PORTF_DATA_R ^= 0x02; // Toggle red led(0.5sec)
			cnt=0;
		}
	}
}


#include "tm4c123gh6pm.h"
#include "PLL.h"

void PLL_Init(void)
{
	// Use RCC2 bcuz it provides more options.
	// The RCC2 register fields override the RCC register fields.
	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
	// 1st step; SET BYPASS2 bit, 
	// at this point the PLL is bypassed and there is no system clock divider.
	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
	// 2nd step; specify the crystal frequency by setting XTAL bits
	// SET OSCSRC2 (XTAL freq. table)
	SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;	 // clear XTAL field,
	SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;   // configure for 16MHz crystal
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M; // clear oscillator source
	SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO; // configure for Main Oscillator source
	// 3rd step;
	// CLEAR PWRDN2 to activate PLL
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
	// 4th step; configure SYSDIV2(n)
	// then the clock will be divided by n+1.(to get 80MHz from 400Mhz, n=4 so 400Mhz/(4+1)=80Mhz)
	SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400; // 400MHz PLL
//	SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000); // clear bits 28:23(SYSDIV2)
	SYSCTL_RCC2_R |= 4<<22;			 // (SYSDIV2=4)
	// 5th step;
	// Wait SYSCTL_RIS_R to become high
	while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS)==0);
	// CLEAR BYPASS2 bit to enable PLL
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}



/* Phase-Lock-Loop, which allows the software to both utilize
	an accurate crystal and to select how fast the computer executes. */
// PLL allows us to speed up(faster) or slow down(long battery) the clock.
// so, it's a trade of between speed & power.
// PLL let us where we want to be.       

// SYSDIV2 = 4
// bus frequency: 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz
void PLL_Init(void);

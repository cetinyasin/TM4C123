

// PF4(SW0) interrupt on falling edge


	// Vector Number 46, Interrupt Number 30
	// Interrupt 0-31 Set Enable(EN0)
	// Interrupt 28-31 Priority(PRI7)
	// Bits 23:21 - Interrupt[4n+2]
	// 0 highest, 7 lowest
	
	void EdgeInt_Init(void);
	
	
	
	
	/* NOTE
	DIR   IS  IBE  IEV  IME   MODE
	--------------------------------
	 0    0   0    0    1    falling
	 0    0   0    1    1    rising
	 0    0   1    X    1     both
	 */
	 
		// PRI (3bit), 0 to 7. (0 highest, 7 lowest)
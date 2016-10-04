// Sample rate 125k samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller
// PE2 - AIN1

void ADC_Init(void);

// busy wait sync
unsigned long ADC0_IN(void);

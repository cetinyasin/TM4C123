
#include "Delay.h"

// 0.1 sec delay
void Delay100ms(unsigned long time)
{
  unsigned long i;
  while(time > 0)
	{
    i = 1333333; // means 100ms
    while(i > 0)
		{
      i = i - 1;
    }
    time = time - 1; 
  }
}

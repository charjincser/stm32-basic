#include <utility.h>

void delay_ms(INT8U delaytime)
{
	unsigned int i;
	for(; delaytime != 0; delaytime--)
	{
		i = 10301;
		while(i--);
	}
}

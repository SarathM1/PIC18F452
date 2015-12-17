#include<p18f452.h>
#pragma config WDT = OFF
#define SW PORTDbits.RD2

void main()
{
	//TRISDbits.RD2 = 1			//Default input
	TRISB = 0;
	while(1)
	{
		if(SW==1)
			PORTB = 0x55;
		else
			PORTB = 0xAA;
	}
}
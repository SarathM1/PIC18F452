#include<p18f452.h>
#pragma config WDT = OFF

void delay(char n)
{
	int i;
	for(i=0;i<=5000;i++)
		for(;n>=0;n--);
}

void main()
{
	TRISBbits.RB0 = 0;
	while(1)
	{
		PORTBbits.RB0 = 0;
		delay(2);
		PORTBbits.RB0 = 1;
		delay(2);
	}
}
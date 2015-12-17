#include<p18f452.h>
#pragma config WDT = OFF

void delay(int n)
{
	int i;
	for(;n>=0;n--)
		for(i=0;i<=5000;i++);
}

void main()
{	
	int i;
	TRISB = 0;
	for(i=0;i<=0xff;i++)
	{
		PORTB = i;
		delay(0);
	}
	for(i=0xff;i>=0;i--)
	{
		PORTB = i;
		delay(0);
	}
}



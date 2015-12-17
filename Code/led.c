#include<p18f452.h>
#pragma config WDT = OFF

void delay(char n)
{
	int i, j;
	for(i=0;i<5000;i++)
	for(j=0;j<0;j++);
}

void main()
{	
	int i;
	TRISB = 0;
	for(i=0;i<=0xff;i++)
	{
		LATB = i;
		delay(0);
	}
	for(i=0xff;i>=0;i--)
	{
		LATB = i;
		delay(0);
	}
}



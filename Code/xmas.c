#include<p18f452.h>
#pragma config WDT = OFF
#define DEL_SMALL 5
#define DEL_LARGE 10
void delay(int n)
{
	int i;
	for(;n>=0;n--)
		for(i=0;i<=5000;i++);	
}

void pattern1()
{
	// Hex counter
	int i;
	for(i=0;i<=0xff;i++)	// Up counter
	{
		PORTB = i;
		delay(DEL_SMALL);
	}
	
}

void main()
{
	TRISB = 0;
	while(1)
	{
		pattern1();
	}
}
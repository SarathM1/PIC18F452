#include<p18f452.h>
#pragma config WDT = OFF

#define DEL 5
#define SW1 PORTDbits.RD0
#define SW2 PORTDbits.RD1

void pattern1();
void pattern2();
void pattern3();

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
		delay(DEL);
	}
}

void pattern2()
{
	int i,j;
	for(i=0;i<=7;i++)
	{
		PORTB = 1<<i;
		delay(DEL);
	}
	for(i=7;i>=0;i--)
	{
		PORTB = 1<<i;
		delay(DEL);
	}	
}

void pattern3()
{
	PORTB = 0XAA;
	delay(DEL+5);
	PORTB = 0X55;
	delay(DEL+5);
}

void main()
{	
	int sel;

	TRISB = 0;
	TRISD = 0x03;
	
	while(1)
	{
		sel = 0;
		
		if(SW1==1)
			sel |= 1;
		if(SW2==1)
			sel |= 2;
		
		switch(sel)
		{
			case 0:
				pattern1();
				break;
			case 1:
				pattern2();
				break;
			case 2:
				pattern3();
				break;
		}
		
	}
}
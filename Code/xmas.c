#include<p18f452.h>
#pragma config WDT = OFF

#define DEL 5
#define LED PORTBbits.RB7

void pattern1();
void pattern2();
void pattern3();
void inter_init();

int flag = 0;
int sel=0;

void inter_init()
{
	INTCONbits.INT0IF = 0;
	INTCONbits.INT0IE = 1;
	INTCONbits.GIE = 1;
}

#pragma interrupt int0_isr
void int0_isr()
{
	if(INTCONbits.INT0IF==1)
	{
		flag = 1;
		LED = ~LED;
		INTCONbits.INT0IF = 0;
	}

}

#pragma code HiPrio_int = 0x08
void HiPrio_int()
{
	_asm
		GOTO int0_isr
	_endasm
}

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
		if(flag)
		{
			PORTD = 0;
			sel++;
			flag = 0;
			break;
		}	
		PORTD = i;
		delay(DEL);
	}
}

void pattern2()
{
	int i,j;
	
	for(i=0;i<=7;i++)
	{
		if(flag)
		{
			break;
		}

		PORTD = 1<<i;
		delay(DEL);
	}
	for(i=7;i>=0;i--)
	{
		if(flag)
		{
			PORTD = 0;
			sel++;
			flag = 0;
			break;
		}

		PORTD = 1<<i;
		delay(DEL);
	}	
}

void pattern3()
{
	if(flag)
	{
		PORTD = 0;
		sel++;
		flag = 0;
	}
	PORTD = 0XAA;
	delay(DEL+5);
	PORTD = 0X55;
	delay(DEL+5);
}

void main()
{	
	TRISD = 0;
	TRISBbits.RB7 = 0;
	
	inter_init();

	while(1)
	{	
		if(sel==3)
			sel = 0;

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
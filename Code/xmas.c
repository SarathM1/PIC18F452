#include<p18f452.h>

#pragma config WDT = OFF

#define DEL 200
#define LED PORTBbits.RB7

void pattern1();
void pattern2();
void pattern3();
void inter_init();
void chk_isr();

int flag = 0;
int sel=0;
unsigned char check = 0;
int cntr = 0;

/*****************High priority interrupt vector **************************/
#pragma code HiPrio_int = 0x08	// Changes the currect code section to address 0x08
void HiPrio_int()
{
	_asm
		GOTO chk_isr
	_endasm
}
#pragma code					// #pragma code with no name changes code section to default address


#pragma interrupt chk_isr
void chk_isr()
{
	if(INTCONbits.INT0IF==1)
	{
		flag = 1;
		INTCONbits.INT0IF = 0;
	}
	
	if (INTCONbits.TMR0IF)
	{  
		INTCONbits.TMR0IF = 0;                 
		TMR0H = 0xF6;        //Timer Reload to count 1ms
		TMR0L = 0x3C;                    
		check = 1;
    }

}

void inter_init()
{
	INTCONbits.INT0IF = 0;
	INTCONbits.TMR0IE = 1;
	INTCONbits.INT0IE = 1;
	INTCONbits.GIE = 1;

	T0CON = 0x00;                 //prescaler 1:2, Timer Stopped
	TMR0H = 0xF6;                 //Timer Reload to count 1ms
	TMR0L = 0x3C;                    
}


void delay_ms(int del)
{
	check = 0;			// 'check' is set every ms in isr when timer starts
	T0CON = 0x80;       //Prescaler 1:2, Timer Started!!
	while(del)
	{
		if(check)
		{
			del--;
			check = 0;
		}
	}
	T0CON = 0x00;       //Prescaler 1:2, Timer Stopped!!
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
		delay_ms(DEL);
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
		delay_ms(DEL);
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
		delay_ms(DEL);
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
	delay_ms(DEL+5);
	PORTD = 0X55;
	delay_ms(DEL+5);
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
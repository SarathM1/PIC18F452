#include <p18f452.h>

#pragma config WDT = OFF

#define LED PORTDbits.RD0
unsigned char check = 0;
int cntr = 0;

void high_isr(void);
void timer_init();

/*****************High priority interrupt vector **************************/
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
  _asm GOTO high_isr _endasm
}

#pragma code
/*****************High priority ISR **************************/

#pragma interrupt high_isr
void high_isr (void)
{
	if (INTCONbits.TMR0IF)
	{  
		INTCONbits.TMR0IF = 0;                 
		TMR0H = 0xF6;        //Timer Reload to count 1ms
		TMR0L = 0x3C;                    
		check = 1;
    }
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

void timer_init()
{
	/*****************Setting Interrupt ********************/
	INTCON = 0x20;                
	/*****************Setting Timer ************************/
	T0CON = 0x00;                 //prescaler 1:2, Timer Stopped
	TMR0H = 0xF6;                 //Timer Reload to count 1ms
	TMR0L = 0x3C;                    
	INTCONbits.GIE = 1;          //enable interrupts

}

void main(void)
{
	TRISDbits.RD0 = 0;
	timer_init();
	/*****************Main Program **************************/
	while(1)
	{
		LED = ~LED;
		delay_ms(1000);
	}
}


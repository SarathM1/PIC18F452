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
		cntr++;
		if(cntr==1000)
		{
			check = 1;
			cntr = 0;
		}
    }
}

void timer_init()
{
	/*****************Setting Interrupt ********************/
	INTCON = 0x20;                
	/*****************Setting Timer ************************/
	T0CON = 0x80;                 //set up timer0 - prescaler 1:2
	TMR0H = 0xF6;                 //Timer Reload to count 1ms
	TMR0L = 0x3C;                    
	INTCONbits.GIE = 1;          //enable interrupts

}

void main(void){

	TRISDbits.RD0 = 0;
	timer_init();
	/*****************Main Program **************************/
	while(1){
		if (check == 1)
		{
			LED = ~LED;			// Turn On LED BackLight
			check = 0;
		}
	}
}


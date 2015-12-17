#include<p18f452.h>
#pragma config WDT = OFF

#define LED PORTBbits.RB7

void chk_isr(void);
void INT0_ISR(void);

#pragma interrupt chk_isr
void chk_isr(void)
{
	if(INTCONbits.INT0IF==1)
		INT0_ISR();
}

#pragma code HiPrio_Int = 0x08
void HiPrio_Int(void)
{
	_asm
		GOTO chk_isr
	_endasm
}

void main()
{
	TRISBbits.TRISB7=0;
	//TRISBbits.TRISB0=1;
	INTCONbits.INT0IF = 0;
	INTCONbits.INT0IE = 1;
	INTCONbits.GIE = 1;
	while(1);
}

void INT0_ISR(void)
{
	LED = ~LED;
	INTCONbits.INT0IF = 0;
}
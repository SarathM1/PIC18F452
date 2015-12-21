#include<p18f452.h>

#pragma config WDT = OFF

#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define E PORTDbits.RD2

#define LCD_DATA PORTB

unsigned char timer_flag = 0;

void high_isr(void);
void timer_init();
void lcd_init();
void lcd_data(char);
void lcd_com(char);

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
		timer_flag = 1;
    }
}

void delay_ms(int del)
{
	timer_flag = 0;			// 'check' is set every ms in isr when timer starts
	T0CON = 0x80;       //Prescaler 1:2, Timer Started!!
	while(del)
	{
		if(timer_flag)
		{
			del--;
			timer_flag = 0;
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

void lcd_data(char data)
{
	LCD_DATA = data;
	RS = 1;
	RW = 0;
	E = 1;
	delay_ms(20);
	E = 0;
}

void lcd_com(char com)
{
	LCD_DATA = com;
	RS = 0;
	RW = 0;
	E = 1;
	delay_ms(20);
	E = 0;
}

void lcd_init()
{
	lcd_com(0x01);	//Clear lcd
	lcd_com(0x02);	// Return Home
	lcd_com(0x0C);	// Display on, cursor off
}

void lcd_string(char *str)
{
	char i;
	for(i=0;str[i]!='\0';i++)
		lcd_data(str[i]);
}

void main()
{
	char str[] = "Hello World!!";
	TRISDbits.RD0 = 0;
	TRISDbits.RD1 = 0;
	TRISDbits.RD2 = 0;
	
	TRISB = 0;

	timer_init();
	lcd_init();
	lcd_string(str);
	while(1);
}
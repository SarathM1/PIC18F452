#include<p18f452.h>
#pragma config WDT = OFF
#define LED PORTBbits.RB0
void delay(int n)
{
	int i;
	for(;n>=0;n--)
		for(i=0;i<=5000;i++);

}

void main()
{
	TRISBbits.RB0 = 0;
	while(1)
	{
		LED = 0;
		delay(10);
		LED = 1;
		delay(10);
	}
}
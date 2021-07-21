/*
 * MIRROR_TOUCH_2.c
 *
 * Created: 10/18/2020 8:32:31 PM
 *  Author: ideapad510
 */ 

#include "adcmodule.h"
#include "uart.h"
#include "minohelper.h"
#include <avr/io.h>

int main(void)
{
	ADC_INIT (ADC_DIVISION_16,ADC_AVCC,SINGLE_MODE , ADC_INTERRUPT_DISABLE,left );
	/*testing*/
		USART_INIT(ASYNCHRONOUS_NORMAL,INT_disable,TX_RX_ENABLE,PARITY_DISABLE_1STOP,DATA_8,USART_BAUD_9600);
/*
gpio_outputconfg(PORTB_DDRA_ADDRESS,PORTB_OUTMOD_ADDRESS,OUTPASS,0);
*/
/*
gpio_outputconfg(PORTA_DDRA_ADDRESS,PORTA_OUTMOD_ADDRESS,OUTPASS,0);
setbit(*PORTA_OUT_ADDRESS,0);*/
volatile unsigned char x=0,y;
	USART_SEND_str("started");

    while(1)
    {
		_delay_ms(50);
	x=ADC_READ(ADC1,_8_BIT);
	
	/*
	y=ADC_READ(ADC0,_8_BIT);
	if (x>y)
	{
		x=x-y;
	}
	else
	{
		x=y-x;
	}
	*/


			/*testing*/
           unsigned char  the_return[8];
           USART_SEND_ARRAY(the_return,inttostring(the_return,x));
           USART_SEND_str("\n");
		
	/*	do{
			
		}	
	   while(x!=255);
	   clearbit(*PORTB_OUT_ADDRESS,0);
	   */
	  
    }
}
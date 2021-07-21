/*
 * uart.c
 *
 * Created: 16/11/2018 01:47:06 م
 *  Author: ideapad510
 */ 
#include "uart.h"

	void USART_INIT(usart_mode mode_of_sync,usart_int intrupts,USART_ENABLE usarttype_TX_RX,USART_CONTORL_FRAME controlframe,USART_DATA_FRAME dataframe,USART_BAUDE_RATES buade_rate)
	{  
		uint16 ubrr_=0;
		 gpio_outputconfg(PORTD_DDRA_ADDRESS,PORTD_OUTMOD_ADDRESS,OUTPASS,1);
		  gpio_inputconfg(PORTD_DDRA_ADDRESS,PORTD_INMOD_ADDRESS,FLOAT_mod,0);
		  
		  







	  
		UCSRC_Access=0x80|mode_of_sync|controlframe|dataframe;
	  UCSRB_Access |= intrupts|usarttype_TX_RX;
	   UCSRB_Access|=dataframe>>8;
	
	  
	  
	  UCSRA_Access|=(mode_of_sync>>8)|mult_mcus_comm_mode;
		if ((mode_of_sync==SYNC_sample_FALLING) ||(mode_of_sync==SYNC_sample_RISING))
		{
	     #if _MASTER_ ==1  
		 gpio_outputconfg(PORTB_DDRA_ADDRESS,PORTB_OUTMOD_ADDRESS,OUTPASS,0);
	     #else
		 gpio_inputconfg(PORTB_DDRA_ADDRESS,PORTB_INMOD_ADDRESS,FLOAT_mod,0);
         #endif
		 ;
		}
	
		  switch (mode_of_sync)
		{case ASYNCHRONOUS_NORMAL:ubrr_= (F_CPU/(16UL*buade_rate)-1);
			                       break;
			case ASYNCHRONOUS_DOUBLE:ubrr_= (F_CPU/(8UL*buade_rate)-1);
			                       break;
			
			case SYNC_sample_RISING:
			case SYNC_sample_FALLING:
			                        ubrr_= (F_CPU/(2.0*buade_rate)-1);
			                        break;
									
		}
		
		
		
		 UBRRL_Access=0xff & ubrr_;
		  UBRRH_Access=0x0f & (ubrr_>>8);
		 
		 
	}
	void USART_SEND_BYTE(uint8 data)
	{
		
		
		UDR_Access=data;
		
		while(isbitclear(UCSRA_Access,UDRE_))
		{}
		
		
	}
	uint8 USART_RECV_BYTE()
	{
			while(isbitclear(UCSRA_Access,RXC_))
			{}
		return UDR_Access;
		
	}
	void USART_SEND_ARRAY(uint8* ptr,uint8 size)
	{uint8 i=0;
		for(i=0;i<size;i++)
		{
			USART_SEND_BYTE(ptr[i]);	
		}
		
	}
	void USART_SEND_str(uint8* ptr)
	{  uint8 i=0;
		while(ptr[i]!='\0')
		{
			USART_SEND_BYTE(ptr[i]);
			_delay_ms(1);
			++i;
		}
		USART_SEND_BYTE('\0');
		}
		
		void USART_RECV_ARRAY(uint8*ptr)
		{   uint8 i=0;
			
			
			do 
			{ptr[i]=USART_RECV_BYTE();
			i++;
			
			} while (ptr[i-1]!=13);
			ptr[i-1]='\0';
			
		}
		
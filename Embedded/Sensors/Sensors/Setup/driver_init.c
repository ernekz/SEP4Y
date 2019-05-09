/*
 * m_driver_initialization.c
 *
 * Created: 5/8/2019 2:20:54 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void driver_init()
{
	stdioCreate(0);
	
	sei(); // enables interrupts
	
	/*
		Initialize the Temperature Driver
	*/
	//if ( HIH8120_OK == hih8120Create() )
	//{
		//printf("Driver created.\n");
	//}
	
	/*
		Initialize LoRa Driver
	*/
	
	hal_create(LED_TASK_PRIORITY);
	lora_driver_create(ser_USART1);	
}



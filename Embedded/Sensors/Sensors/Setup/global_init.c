/*
 * m_driver_initialization.c
 *
 * Created: 5/8/2019 2:20:54 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void measure_co2_callback(uint16_t ppm);

MessageBufferHandle_t xMessageBuffer;

SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xSemaphore_print;

void global_init()
{
	stdioCreate(0);
	
	sei(); // enables interrupts
	
	xSemaphore = xSemaphoreCreateMutex();
	xSemaphore_print = xSemaphoreCreateBinary();
	
	xSemaphoreGive(xSemaphore_print);
	
	xMessageBuffer = xMessageBufferCreate( sizeof (m_data) * 3);
		
	/*
		Initialize LoRa Driver
	*/

	hal_create(LED_TASK_PRIORITY);
	lora_driver_create(ser_USART1);
	m_print("LoRa driver created.\n",xSemaphore_print);
	
	/*
		Initialize the Temperature Driver
	*/
	if ( HIH8120_OK == hih8120Create() )
	{
		m_print("Temp/Humidity driver created.\n",xSemaphore_print);
	}
	
	/*
		Initialize MH-Z19 CO2 Driver
	*/
	mh_z19_create(ser_USART3, measure_co2_callback);
	m_print("CO2 driver created.\n",xSemaphore_print);
	
}



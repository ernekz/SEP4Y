/*
 * m_driver_initialization.c
 *
 * Created: 5/8/2019 2:20:54 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void measure_co2_callback(uint16_t ppm);


QueueHandle_t xQueue;

SemaphoreHandle_t xSemaphore_co2;
SemaphoreHandle_t xSemaphore_print;
SemaphoreHandle_t xSemaphore_temperature;
SemaphoreHandle_t xSemaphore_view_data;
SemaphoreHandle_t xSemaphore_buffer;

void global_init()
{
	stdioCreate(0);
	
	sei(); // enables interrupts
	
	xSemaphore_print = xSemaphoreCreateBinary();
	
	xSemaphore_co2 = xSemaphoreCreateMutex();
	xSemaphore_temperature = xSemaphoreCreateMutex();
	xSemaphore_view_data = xSemaphoreCreateMutex();
	xSemaphore_buffer = xSemaphoreCreateMutex();
	
	xSemaphoreGive(xSemaphore_print);
	
	xQueue = xQueueCreate(2,sizeof (m_data));
	
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



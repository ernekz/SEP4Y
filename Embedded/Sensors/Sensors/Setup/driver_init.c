/*
 * m_driver_initialization.c
 *
 * Created: 5/8/2019 2:20:54 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void measure_co2_callback(uint16_t ppm);

SemaphoreHandle_t xSemaphore_temp;
SemaphoreHandle_t xSemaphore_co2;

MessageBufferHandle_t xMessageBuffer_temp;
MessageBufferHandle_t xMessageBuffer_co2;

void driver_init()
{
	stdioCreate(0);
	
	sei(); // enables interrupts
	
	xSemaphore_temp = xSemaphoreCreateMutex();
	xSemaphore_co2 = xSemaphoreCreateMutex();
	
	xMessageBuffer_temp = xMessageBufferCreate( sizeof (int));
	xMessageBuffer_co2 = xMessageBufferCreate( sizeof (uint16_t));
	
	/*
		Initialize the Temperature Driver
	*/
	if ( HIH8120_OK == hih8120Create() )
	{
		xSemaphoreTake(xSemaphore_temp, portMAX_DELAY);
		printf("Temp/Humidity driver created.\n");
		xSemaphoreGive(xSemaphore_temp);
	}
	
	/*
		Initialize LoRa Driver
	*/
	
	hal_create(LED_TASK_PRIORITY);
	lora_driver_create(ser_USART1);
	printf("LoRa driver created.\n");
	
	/*
		Initialize MH-Z19 CO2 Driver
	*/
	
	mh_z19_create(ser_USART3, measure_co2_callback);
	xSemaphoreTake(xSemaphore_temp, portMAX_DELAY);
	printf("Temp/Humidity driver created.\n");
	xSemaphoreGive(xSemaphore_temp);
}



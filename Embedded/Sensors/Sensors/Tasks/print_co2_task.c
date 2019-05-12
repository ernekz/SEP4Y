/*
 * print_co2_task.c
 *
 * Created: 5/12/2019 2:59:57 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

MessageBufferHandle_t xMessageBuffer_co2;
SemaphoreHandle_t xSemaphore_co2;

void print_co2_task(void *pvParameters)
{
	uint16_t recieved_data;
	size_t xRecievedBytes;
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
		
		xRecievedBytes = xMessageBufferReceive(xMessageBuffer_co2
							,(void *) recieved_data
							, xRecievedBytes
							,0 );
		
		xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
		printf("Received CO2 level : %d ppm\n",recieved_data);
		xSemaphoreGive(xSemaphore_co2);
		vTaskDelay(10);
	}
	vTaskDelete(NULL);
}
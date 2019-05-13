/*
 * print_temperature_task.c
 *
 * Created: 5/10/2019 1:48:43 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"



void print_temp_task(void *pvParameters)
{
	int temperature; 
	size_t xRecievedBytes;
	
	while (1)
	{ 
		xSemaphoreTake(xSemaphore_temp, portMAX_DELAY);
		
		xRecievedBytes = xMessageBufferReceive( xMessageBuffer_temp
							, &temperature
							, sizeof (int)
							,0 );
		
							
		for (int i = 0; i < xRecievedBytes; i++)
		{
			vTaskDelay(100/portTICK_PERIOD_MS);
			xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
			printf("\nReceived temperature: %d\n\n",temperature);
			xSemaphoreGive(xSemaphore_temp);
			vTaskDelay(1);	
		}
	}
	vTaskDelete(NULL);	
}
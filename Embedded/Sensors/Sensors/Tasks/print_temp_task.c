/*
 * print_temperature_task.c
 *
 * Created: 5/10/2019 1:48:43 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

SemaphoreHandle_t xSemaphore_temp;
MessageBufferHandle_t xMessageBuffer_temp;



void print_temp_task(void *pvParameters)
{
	int data_to_receive[2];
	size_t xRecievedBytes;
	
	while (1)
	{ 
		xSemaphoreTake(xSemaphore_temp, portMAX_DELAY);
		
		xRecievedBytes = xMessageBufferReceive( xMessageBuffer_temp
							, (void *)data_to_receive
							, sizeof (data_to_receive)
							,0 );
							
		for (int i = 0; i < xRecievedBytes; i++)
		{
			//vTaskDelay(10/portTICK_PERIOD_MS);
			xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
			printf("Received temperature: %d\n",data_to_receive[i]);
			xSemaphoreGive(xSemaphore_temp);
			vTaskDelay(1);	
		}
	}
	vTaskDelete(NULL);	
}
/*
 * measure_temp_task.c
 *
 * Created: 5/9/2019 3:41:03 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

SemaphoreHandle_t xSemaphore_temp;
MessageBufferHandle_t xMessageBuffer_temp;



void measure_temp_task(void *pvParameters)
{	
	int data_to_send[2];
	int temperature = 0;
	
	while (1)
	{		
		xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
		
		if ( HIH8120_OK != hih8120Wakeup() )
		{
			//xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
			printf("Error in waking up the temp/humidity driver!\n");
			//xSemaphoreGive(xSemaphore_temp);
		}
		
		vTaskDelay(50/portTICK_PERIOD_MS);
		
		for (int i = 0; i < 2; i++)
		{
			if ( HIH8120_OK !=  hih8120Meassure() )
			{
				//xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
				printf("Error in measuring the temperature!\n");
				//xSemaphoreGive(xSemaphore_temp);
				i--;
			}
			else
			{
				
				vTaskDelay(10/portTICK_PERIOD_MS);
				temperature = hih8120GetTemperature_x10();
				data_to_send[i] = temperature;
				
				xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
				printf("Temperature %d sent!\n",data_to_send[i]);
				xSemaphoreGive(xSemaphore_temp);
				vTaskDelay(1);
			}
		}
		xMessageBufferSend(xMessageBuffer_temp
		, (void *) data_to_send
		, sizeof (data_to_send)
		, 0);
		
		printf("Temperature sent to the message buffer!\n");
	}
	vTaskDelete(NULL);
}
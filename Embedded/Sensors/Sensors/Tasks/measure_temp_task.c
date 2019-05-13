/*
* measure_temp_task.c
*
* Created: 5/9/2019 3:41:03 PM
*  Author: drags
*/

#include "../Headers/m_lora_includes.h"

void measure_temp_task(void *pvParameters)
{
	int temperature = 0;
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
		
		if ( HIH8120_OK != hih8120Wakeup() )
		{
			m_print("Error in waking up the censors!",xSemaphore_temp);
		}
		
		vTaskDelay(50/portTICK_PERIOD_MS);
		
	
		if ( HIH8120_OK !=  hih8120Meassure() )
		{
			m_print("Error in measuring the temperature!",xSemaphore_temp);			
		}
		else
		{	
			vTaskDelay(100/portTICK_PERIOD_MS);
			temperature = hih8120GetTemperature_x10();
				
			xSemaphoreTake(xSemaphore_temp,portMAX_DELAY);
			printf("Temperature %d sent!\n", temperature);
			xSemaphoreGive(xSemaphore_temp);
			//vTaskDelay(1);
		}
		xMessageBufferSend(xMessageBuffer_temp
		, &temperature 
		, sizeof (int)
		, 0);
		
		printf("Temperature sent to the message buffer!\n");
	}
}
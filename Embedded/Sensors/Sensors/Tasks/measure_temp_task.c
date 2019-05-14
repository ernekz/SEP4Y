/*
* measure_temp_task.c
*
* Created: 5/9/2019 3:41:03 PM
*  Author: drags
*/

#include "../Headers/m_lora_includes.h"

void lora_reset();

void measure_temp_task(void *pvParameters)
{
	m_data temperature; 
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_temperature, portMAX_DELAY);

		if ( HIH8120_OK != hih8120Wakeup() )
		{
			m_print("Error in waking up the sensors!",xSemaphore_print);
		}
		
		vTaskDelay(100/portTICK_PERIOD_MS);
		
	
		if ( HIH8120_OK !=  hih8120Meassure() )
		{
			m_print("Error in measuring the temperature!",xSemaphore_print);			
		}
		else
		{	
			vTaskDelay(50/portTICK_PERIOD_MS);
			temperature.type = 2;
			temperature.value = hih8120GetTemperature_x10();
				
			if (xQueueSend(xQueue, (void *) &temperature, portMAX_DELAY) != pdPASS)
			{
				m_print("Queue is full! Failed to send temperature!\n",xSemaphore_print);
			}
		}
		vTaskDelay(10000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
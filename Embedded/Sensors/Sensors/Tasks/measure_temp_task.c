/*
* measure_temp_task.c
*
* Created: 5/9/2019 3:41:03 PM
*  Author: drags
*/

#include "../Headers/m_lora_includes.h"

void measure_temp_task(void *pvParameters)
{
	m_data temperature = {2, 0};
	
	while (1)
	{
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		
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
			vTaskDelay(300/portTICK_PERIOD_MS);
			temperature.value = hih8120GetTemperature_x10();
				
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Temperature(type: %d, val: %d) sent!\n", temperature.type,temperature.value);
			xSemaphoreGive(xSemaphore_print);
			//vTaskDelay(1);
		}
		
		xMessageBufferSend(xMessageBuffer
		, &temperature 
		, sizeof (m_data)
		, 0);
		
		m_print("Temperature sent to the message buffer!\n",xSemaphore_print);
	}
}
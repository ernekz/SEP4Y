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
	m_data temperature = {2, 0};
	
	//lora_reset();
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_temperature, portMAX_DELAY);
		
		m_print("\nMeasuring Temperature Task running!\n",xSemaphore_print);
		

		if ( HIH8120_OK != hih8120Wakeup() )
		{
			m_print("Error in waking up the sensors!",xSemaphore_print);
		}
		
		vTaskDelay(50/portTICK_PERIOD_MS);
		
	
		if ( HIH8120_OK !=  hih8120Meassure() )
		{
			m_print("Error in measuring the temperature!",xSemaphore_print);			
		}
		else
		{	
			vTaskDelay(10/portTICK_PERIOD_MS);
			temperature.value = hih8120GetTemperature_x10();
				
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Temperature(type: %d, val: %d) sent!\n", temperature.type,temperature.value);
			xSemaphoreGive(xSemaphore_print);
			write_to_buffer(xMessageBuffer,temperature);
		}
		
		m_print("Temperature sent to the message buffer!\n",xSemaphore_print);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
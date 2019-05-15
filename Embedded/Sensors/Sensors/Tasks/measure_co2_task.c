/*
 * measure_co2_task.c
 *
 * Created: 5/11/2019 5:51:38 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void measure_co2_task(void *pvParameters)
{
	m_data co2; 
	
	while (1)
	{
		
		xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
		
		if (mh_z19_take_meassuring() != MHZ19_OK)
		{
			m_print("Error measuring CO2 value!\n",xSemaphore_print);
		}
	
		//vTaskDelay(1000/portTICK_PERIOD_MS);
		
		co2.type = 1;
		co2.value = co2_value;
		
		xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
		printf("CO2 in task: %d\n",co2_value);
		xSemaphoreGive(xSemaphore_print);
		
		if (xQueueSend(xQueue, (void *) &co2, portMAX_DELAY) != pdPASS)
		{
			m_print("Queue is full! Failed to send CO2!\n",xSemaphore_print);
		}
		
		//vTaskDelay(10000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
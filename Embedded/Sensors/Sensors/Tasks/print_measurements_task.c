/*
 * print_co2_task.c
 *
 * Created: 5/12/2019 2:59:57 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void print_measuremenets_task(void *pvParameters)
{
	m_data data;
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
		
		m_print("\nMeasurements Printing task running!\n",xSemaphore_print);
		
		if (xQueueReceive(xQueue, &(data), 0) != pdTRUE)
		{
			m_print("Unable to receive data from queue!\n",xSemaphore_print);
		}
		else
		{
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Received measurement: type: %d, val: %d\n\n",data.type, data.value);
			xSemaphoreGive(xSemaphore_print);
		}
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
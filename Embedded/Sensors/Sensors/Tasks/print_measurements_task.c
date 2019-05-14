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
	size_t xRecievedBytes;
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
		xSemaphoreTake(xSemaphore_buffer, portMAX_DELAY);
		
		
		m_print("\nMeasurements Printing task running!\n",xSemaphore_print);
		
		xRecievedBytes = xMessageBufferReceive(xMessageBuffer
							,&data
							, sizeof(m_data)
							,0 );
		
		
		for (int i = 0; i < xRecievedBytes; i++)
		{
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Received measurement: type: %d, val: %d\n\n",data.type, data.value);
			vTaskDelay(1);
			xSemaphoreGive(xSemaphore_print);
		}
		xSemaphoreGive(xSemaphore_buffer);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
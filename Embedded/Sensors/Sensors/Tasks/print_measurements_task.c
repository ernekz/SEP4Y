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
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		
		xRecievedBytes = xMessageBufferReceive(xMessageBuffer
							,&data
							, sizeof(m_data)
							,0 );
		
		
		for (int i = 0; i < xRecievedBytes; i++)
		{
			vTaskDelay(100/portTICK_PERIOD_MS);
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Received measurement: type: %d, val: %d\n\n",data.type, data.value);
			xSemaphoreGive(xSemaphore_print);
			vTaskDelay(1);
		}
	}
	vTaskDelete(NULL);
}
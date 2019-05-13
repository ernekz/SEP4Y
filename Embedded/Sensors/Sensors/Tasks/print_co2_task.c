/*
 * print_co2_task.c
 *
 * Created: 5/12/2019 2:59:57 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void print_co2_task(void *pvParameters)
{
	uint16_t ppm;
	size_t xRecievedBytes;
	
	while (1)
	{
		xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
		
		xRecievedBytes = xMessageBufferReceive(xMessageBuffer_co2
							,&ppm
							, sizeof(uint16_t)
							,0 );
		
		
		for (int i = 0; i < xRecievedBytes; i++)
		{
			vTaskDelay(100/portTICK_PERIOD_MS);
			xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
			printf("Received CO2 level : %d ppm\n\n",ppm);
			xSemaphoreGive(xSemaphore_co2);
			vTaskDelay(1);
		}
	}
	vTaskDelete(NULL);
}
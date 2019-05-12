/*
 * measure_co2_task.c
 *
 * Created: 5/11/2019 5:51:38 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

SemaphoreHandle_t xSemaphore_co2;

void measure_co2_task(void *pvParameters)
{
	while (1)
	{
		xSemaphoreTake(xSemaphore_co2, portMAX_DELAY);
		
		if (mh_z19_take_meassuring() != MHZ19_OK)
		{
			printf("Error measuring CO2 ppm!\n");
		}
	}
	vTaskDelete(NULL);
}
/*
 * measure_co2_task.c
 *
 * Created: 5/11/2019 5:51:38 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void measure_co2_task(void *pvParameters)
{
	while (1)
	{
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		
		if (mh_z19_take_meassuring() != MHZ19_OK)
		{
			m_print("Error measuring CO2 value!\n",xSemaphore_print);
		}
	}
}
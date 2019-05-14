/*
 * measure_co2_task.c
 *
 * Created: 5/11/2019 5:51:38 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void measure_co2_task(void *pvParameters)
{
	m_data co2 = {1, 0};
	
	while (1)
	{
		
		xSemaphoreTake(xSemaphore_co2,portMAX_DELAY);
		
		m_print("\nMeasuring CO2 task running!\n",xSemaphore_print);
		
		if (mh_z19_take_meassuring() != MHZ19_OK)
		{
			m_print("Error measuring CO2 value!\n",xSemaphore_print);
		}
	
		co2.value = co2_value;
		
		write_to_buffer(xMessageBuffer, co2);
		xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
		printf("CO2 (type: %d, val: %u) sent!\n", co2.type, (unsigned int)co2.value);
		xSemaphoreGive(xSemaphore_print);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
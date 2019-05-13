/*
 * measure_co2_callback.c
 *
 * Created: 5/11/2019 6:00:59 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void measure_co2_callback(uint16_t ppm)
{
	m_data co2 = {1, ppm};
	
	xMessageBufferSend( xMessageBuffer
					, &co2
					, sizeof (m_data)
					,0);
	
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("CO2 (type: %d, val: %u) sent!\n", co2.type, (unsigned int)co2.value);
	xSemaphoreGive(xSemaphore_print);
}
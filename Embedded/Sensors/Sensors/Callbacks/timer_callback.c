/*
 * timer_5_mins_callback.c
 *
 * Created: 5/14/2019 9:34:37 AM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

void timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore_temperature);

	xSemaphoreGive(xSemaphore_co2);
	
	xSemaphoreGive(xSemaphore_view_data);
	
}
/*
 * measure_timer_callback.c
 *
 * Created: 5/10/2019 1:58:06 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

void measure_temp_timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore_temp);
}



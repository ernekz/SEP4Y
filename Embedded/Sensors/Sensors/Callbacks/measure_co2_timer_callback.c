/*
 * measure_co2_timer_callback.c
 *
 * Created: 5/12/2019 3:28:15 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

SemaphoreHandle_t xSemaphore_co2;
TimerHandle_t xTimer_measure_co2;

void measure_co2_timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore_co2);
}
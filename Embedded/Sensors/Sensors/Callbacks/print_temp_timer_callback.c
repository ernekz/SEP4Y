/*
 * print_temp_timer_callback.c
 *
 * Created: 5/12/2019 5:42:52 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

SemaphoreHandle_t xSemaphore_temp;
TimerHandle_t xTimer_measure_temp;

void print_temp_timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore_temp);
}
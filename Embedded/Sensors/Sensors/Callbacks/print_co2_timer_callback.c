/*
 * print_co2_timer_callback.c
 *
 * Created: 5/12/2019 6:14:37 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"

void print_co2_timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore_co2);
}
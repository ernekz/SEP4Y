/*
 * send_data_timer_callback.c
 *
 * Created: 5/13/2019 6:06:51 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void send_data_timer_callback(TimerHandle_t pxTimer)
{
	xSemaphoreGive(xSemaphore);
}
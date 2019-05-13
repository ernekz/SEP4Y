/*
 * m_print.c
 *
 * Created: 5/13/2019 10:04:35 AM
 *  Author: drags
 */ 
#include "Headers/m_lora_includes.h"

void m_print(char message[], SemaphoreHandle_t xSemaphore)
{
	xSemaphoreTake(xSemaphore, portMAX_DELAY);
	printf("%s\n",message);
	xSemaphoreGive(xSemaphore);
}
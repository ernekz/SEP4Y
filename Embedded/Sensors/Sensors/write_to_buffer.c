/*
 * write_to_buffer.c
 *
 * Created: 5/14/2019 10:44:30 AM
 *  Author: drags
 */ 

#include "Headers/m_lora_includes.h"

void write_to_buffer(MessageBufferHandle_t xMessageBuffer, m_data data)
{
	m_data local_data = data;
	
	xSemaphoreTake(xSemaphore_buffer,portMAX_DELAY);
	xMessageBufferSend( xMessageBuffer
	, &local_data
	, sizeof (m_data)
	,0);
	xSemaphoreGive(xSemaphore_buffer);
}
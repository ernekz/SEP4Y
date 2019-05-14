/*
 * m_includes.h
 *
 * Created: 5/8/2019 2:07:10 PM
 *  Author: drags
 */ 


#ifndef M_INCLUDES_H_
#define M_INCLUDES_H_

#include "ATMEGA_FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdio_driver.h>
#include <avr/interrupt.h>
#include <ihal.h>
#include <lora_driver.h>
#include <stddef.h>
#include <iled.h>
#include <hih8120.h>
#include <avr/io.h>
#include <mh_z19.h>
#include "semphr.h"
#include <timers.h>
#include <hcSr501.h>
#include <message_buffer.h>

#define LORA_appEUI "7933b719938849c4"
#define LORA_appKEY "d4bf3a8e5dd4e7867d983f79f09300ec"

#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define LORA_RESET_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

extern SemaphoreHandle_t xSemaphore_co2;
extern SemaphoreHandle_t xSemaphore_print;
extern SemaphoreHandle_t xSemaphore_temperature;
extern SemaphoreHandle_t xSemaphore_view_data;
extern SemaphoreHandle_t xSemaphore_buffer;

extern MessageBufferHandle_t xMessageBuffer;
extern TimerHandle_t xTimer_5_mins;


extern uint16_t co2_value;

typedef struct measurement{
	int type;
	uint16_t value;
} m_data;


void m_print(char message[], SemaphoreHandle_t pxSemaphore);
void write_to_buffer(MessageBufferHandle_t xMessageBuffer, m_data data);

#endif /* M_INCLUDES_H_ */
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

#define LORA_appEUI "4203716466d93a07"
#define LORA_appKEY "7dc57c5406c0882d3a4d5a9ed7ae5c6f"
#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define LORA_HANDLER_TASK_PRIORITY (tskIDLE_PRIORITY + 1)


void m_print(char message[], SemaphoreHandle_t pxSemaphore);

extern SemaphoreHandle_t xSemaphore;
extern SemaphoreHandle_t xSemaphore_print;

extern MessageBufferHandle_t xMessageBuffer;


extern TimerHandle_t xTimer_measure_temp;
extern TimerHandle_t xTimer_measure_co2;
extern TimerHandle_t xTimer_read_measurements;
extern TimerHandle_t xTimer_send_data;

typedef struct measurement{
	int type;
	uint16_t value;
} m_data;


#endif /* M_INCLUDES_H_ */
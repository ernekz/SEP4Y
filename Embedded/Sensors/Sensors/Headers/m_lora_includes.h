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
#include <stdio_driver.h>



#define LORA_appEUI "4203716466d93a07"
#define LORA_appKEY "7dc57c5406c0882d3a4d5a9ed7ae5c6f"
#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define LORA_HANDLER_TASK_PRIORITY (tskIDLE_PRIORITY + 2)


#endif /* M_INCLUDES_H_ */
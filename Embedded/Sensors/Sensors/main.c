#include <stddef.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ATMEGA_FreeRTOS.h"
#include <mh_z19.h>
#include <ihal.h>
#include "task.h"
#include "semphr.h"
#include <timers.h>
#include <hcSr501.h>
#include <stdio_driver.h>
#include <hih8120.h>
#include "Headers/m_lora_includes.h"



void driver_init();
void create_all_tasks(UBaseType_t lora_handler_task_priority);
void create_all_timers();


TimerHandle_t xTimer_read_temp;
TimerHandle_t xTimer_measure_temp;
TimerHandle_t xTimer_read_co2;
TimerHandle_t xTimer_measure_co2;

MessageBufferHandle_t xMessageBuffer_temp;
MessageBufferHandle_t xMessageBuffer_co2;

SemaphoreHandle_t xSemaphore_temp;

int main(void)
{			
	driver_init();
	
	create_all_tasks(LORA_HANDLER_TASK_PRIORITY);
	
	create_all_timers();
	
	
	
	
	
	//xTimerStart(xTimer_measure_temp,0);
	//xTimerStart(xTimer_read_temp,0);
	xTimerStart(xTimer_measure_co2,0);
	xTimerStart(xTimer_read_co2,0);
					
	vTaskStartScheduler();
	
	while (1)
	{
		;	
	}
}


//#include <stddef.h>
//#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <stdio.h>
//#include "ATMEGA_FreeRTOS.h"
//#include <mh_z19.h>
//#include <ihal.h>
//#include "task.h"
//#include "semphr.h"
//#include <timers.h>
//#include <hcSr501.h>
//#include <stdio_driver.h>
//#include <hih8120.h>
#include "Headers/m_lora_includes.h"



void global_init();
void create_all_tasks(UBaseType_t lora_handler_task_priority);
void create_all_timers();
void lora_setup(void);

int main(void)
{				
	global_init();
	
	create_all_timers();
	
	create_all_tasks(LORA_RESET_TASK_PRIORITY);
	
	xTimerStart(xTimer,0);
					
	vTaskStartScheduler();
	
	
	while (1)
	{
		;	
	}
}


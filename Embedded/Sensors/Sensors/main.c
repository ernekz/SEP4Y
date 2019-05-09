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
void lora_handler_create(UBaseType_t lora_handler_task_priority);

int main(void)
{			
	driver_init();
	
	lora_handler_create(LORA_HANDLER_TASK_PRIORITY);
				
	vTaskStartScheduler();
	
	while (1)
	{
		;	
	}
}


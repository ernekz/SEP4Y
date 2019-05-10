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


#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 10)
#define LORA_HANDLER_TASK_PRIORITY (tskIDLE_PRIORITY + 7)

//void measure_temperature_task(void *pvParameters);

//void measure_co2_task(void *pvParameters);
//void my_co2_call_back(uint16_t ppm);

void lora_handler_create(UBaseType_t lora_handler_task_priority);

//void measure_co2_timer_callback(TimerHandle_t pxTimer);
//void start_timer_task(void *pvParameters);
//
//TimerHandle_t xTimer;
//SemaphoreHandle_t xMutex;

int main(void)
{
	stdioCreate(0);
	
	sei(); // enables interrupts
	
	/*if ( HIH8120_OK == hih8120Create() )
	{
		printf("Driver created.\n");
	}*/
	
	//mh_z19_create(ser_USART3, my_co2_call_back); 
	//xMutex = xSemaphoreCreateMutex();
	//
	hal_create(LED_TASK_PRIORITY);
	lora_driver_create(ser_USART1);
	
	lora_handler_create(LORA_HANDLER_TASK_PRIORITY);

	//xTaskCreate(start_timer_task, "CO2 Timer Task", 
				//configMINIMAL_STACK_SIZE, NULL,
				//tskIDLE_PRIORITY, NULL);
				
	//xTaskCreate(measure_temperature_task, "Temperature Task",
	//configMINIMAL_STACK_SIZE, NULL,
	//tskIDLE_PRIORITY, NULL);
				
	//xMutex = xSemaphoreCreateMutex();
	//xTimerStart(xTimer,0);
	vTaskStartScheduler();
	
	while (1)
	{
		;	
	}
}


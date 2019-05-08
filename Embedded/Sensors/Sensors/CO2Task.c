#include <mh_z19.h>
#include "ATMEGA_FreeRTOS.h"
#include <stdio_driver.h>
#include <stdio.h>
#include <timers.h>
#include "semphr.h"
#include <avr/interrupt.h>
#include "task.h"

TimerHandle_t xTimer;
SemaphoreHandle_t xMutex;

//void measure_co2_task(void *pvParameters)
//{
	//;
//}

void my_co2_call_back(uint16_t ppm)
{
	while (1)
	{
		xSemaphoreTake(xMutex,portMAX_DELAY);
		printf("CO2 level: %d\n",ppm);
		xSemaphoreGive(xMutex);
	}
}

void measure_co2_timer_callback()
{
	mh_z19_return_code_t rc;
	while (1)
	{
		xSemaphoreTake(xMutex,portMAX_DELAY);
		rc = mh_z19_take_meassuring();
		if (rc != MHZ19_OK)
		{
			printf("Something went wrong\n");
		}
		xSemaphoreGive(xMutex);
	}
}

void start_timer_task(void *pvParameters)
{
	xTimer = xTimerCreate("CO2 Timer",
			(1000/portTICK_PERIOD_MS),
			pdTRUE,
			(void*)0,
			measure_co2_timer_callback);
	
	vTaskDelete(NULL);
}
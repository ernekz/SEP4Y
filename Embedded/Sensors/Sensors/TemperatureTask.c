#include "ATMEGA_FreeRTOS.h"
#include <hih8120.h>
#include "stdio_driver.h"
#include <stdio.h>
#include "task.h"


int temperature = 0;

void measure_temperature_task(void *pvParameters)
{
	while (1)
	{
		if (HIH8120_OK != hih8120Wakeup() )
		{
			printf("Something went wrong");
		}
		
		vTaskDelay(50);
		
		if ( HIH8120_OK !=  hih8120Meassure() )
		{
			printf("Can't measure temperate");
		}
		else
		{
			temperature = hih8120GetTemperature_x10();
			printf("Temperature: %d\n", temperature);
		}
	}
	vTaskDelete(NULL);
}
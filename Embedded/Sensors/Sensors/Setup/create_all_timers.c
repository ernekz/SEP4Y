/*
 * create_all_timers.c
 *
 * Created: 5/10/2019 1:59:04 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void measure_temp_timer_callback(TimerHandle_t pxTimer);
void measure_co2_timer_callback(TimerHandle_t pxTimer);
void print_temp_timer_callback(TimerHandle_t pxTimer);
void print_co2_timer_callback(TimerHandle_t pxTimer);

TimerHandle_t xTimer_measure_temp;
TimerHandle_t xTimer_read_temp;
TimerHandle_t xTimer_measure_co2;
TimerHandle_t xTimer_read_co2;

void create_all_timers()
{
	xTimer_measure_temp = xTimerCreate("Temperature Measure Timer",
			(1000/portTICK_PERIOD_MS),
			pdTRUE,
			(void*) 0,
			measure_temp_timer_callback);
	
	xTimer_read_temp = xTimerCreate("Temperature Read Timer",
			(1000/portTICK_PERIOD_MS),
			pdTRUE,
			(void*) 1,
			print_temp_timer_callback);
	
	xTimer_measure_co2 = xTimerCreate("CO2 Measure Timer",
			(1000/portTICK_PERIOD_MS),
			pdTRUE,
			(void*) 2,
			measure_co2_timer_callback);
				
	xTimer_read_co2 = xTimerCreate("CO2 Read Timer",
			(1000/portTICK_PERIOD_MS),
			pdTRUE,
			(void*) 3,
			print_co2_timer_callback);
}
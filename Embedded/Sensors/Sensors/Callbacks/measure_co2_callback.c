/*
 * measure_co2_callback.c
 *
 * Created: 5/11/2019 6:00:59 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

uint16_t co2_value;


void measure_co2_callback(uint16_t ppm)
{
	co2_value = ppm;
}
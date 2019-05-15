/*
 * lora_reset_task.c
 *
 * Created: 5/13/2019 7:30:00 PM
 *  Author: drags
 */ 
#include "../Headers/m_lora_includes.h"


void lora_setup(void);

void lora_reset()
{
	lora_driver_reset_rn2483(1); // Activate reset line
	vTaskDelay(2);
	lora_driver_reset_rn2483(0); // Release reset line
	vTaskDelay(150); // Wait for tranceiver module to wake up after reset
	lora_driver_flush_buffers(); // get rid of first version string from module after reset!
	
	lora_setup();
}
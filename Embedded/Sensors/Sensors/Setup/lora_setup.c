/*
 * lora_setup.c
 *
 * Created: 5/8/2019 2:11:48 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

static char _out_buf[100];

void lora_setup(void)
{
	e_LoRa_return_code_t rc;
	
	/*
		Hardware reset of LoRaWAN transceiver
	*/
	

	led_slow_blink(led_ST2); // OPTIONAL: Led the green led blink slowly while we are setting up LoRa

	// Factory reset the transceiver
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("FactoryReset >%s<\n", lora_driver_map_return_code_to_text(lora_driver_rn2483_factory_reset()));
	xSemaphoreGive(xSemaphore_print);
	
	// Configure to EU868 LoRaWAN standards
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Configure to EU868 >%s<\n", lora_driver_map_return_code_to_text(lora_driver_configure_to_eu868()));
	xSemaphoreGive(xSemaphore_print);

	// Get the transceivers HW EUI
	rc = lora_driver_get_rn2483_hweui(_out_buf);
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Get HWEUI >%s<: %s\n",lora_driver_map_return_code_to_text(rc), _out_buf);
	xSemaphoreGive(xSemaphore_print);

	// Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_map_return_code_to_text(lora_driver_set_device_identifier(_out_buf)));
	xSemaphoreGive(xSemaphore_print);
	
	// Set Over The Air Activation parameters to be ready to join the LoRaWAN
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_map_return_code_to_text(lora_driver_set_otaa_identity(LORA_appEUI,LORA_appKEY,_out_buf)));
	xSemaphoreGive(xSemaphore_print);

	// Save all the MAC settings in the transceiver
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Save mac >%s<\n",lora_driver_map_return_code_to_text(lora_driver_save_mac()));
	xSemaphoreGive(xSemaphore_print);

	// Enable Adaptive Data Rate
	xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_map_return_code_to_text(lora_driver_set_adaptive_data_rate(LoRa_ON)));
	xSemaphoreGive(xSemaphore_print);
	
	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 5;
	do {
		rc = lora_driver_join(LoRa_OTAA);
		printf("Join Network Tries Left:%d >%s<\n", maxJoinTriesLeft, lora_driver_map_return_code_to_text(rc));

		if ( rc != LoRa_ACCEPTED)
		{
			// Make the red led pulse to tell something went wrong
			led_long_puls(led_ST1); // OPTIONAL
			// Wait 5 sec and lets try again
			vTaskDelay(5000/portTICK_PERIOD_MS);
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LoRa_ACCEPTED)
	{
		// Connected to LoRaWAN :-)
		// Make the green led steady
		led_led_on(led_ST2); // OPTIONAL
	}
	else
	{
		// Something went wrong
		// Turn off the green led
		led_led_off(led_ST2); // OPTIONAL
		// Make the red led blink fast to tell something went wrong
		led_fast_blink(led_ST1); // OPTIONAL

		// Lets stay here
		while (1)
		{
			taskYIELD();
		}
	}
}
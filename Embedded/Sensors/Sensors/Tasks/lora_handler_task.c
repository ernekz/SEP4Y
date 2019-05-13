/*
 * lora_handler_task.c
 *
 * Created: 5/9/2019 12:42:56 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void lora_setup(void);


static lora_payload_t _uplink_payload;

/*
	Task that sends data to the server
*/
void lora_handler_task(void *pvParameters)
{
	m_data data;
	size_t xRecievedBytes;
	
	/*
		Hardware reset of LoRaWAN transceiver
	*/
	lora_driver_reset_rn2483(1); // Activate reset line
	vTaskDelay(2); 
	lora_driver_reset_rn2483(0); // Release reset line
	vTaskDelay(150); // Wait for transceiver module to wake up after reset
	lora_driver_flush_buffers(); // get rid of first version string from module after reset!

	lora_setup();

	_uplink_payload.len = 4;
	_uplink_payload.port_no = 2;


	while (1)
	{
		xSemaphoreTake(xSemaphore, 0);
		vTaskDelay(10000/portTICK_PERIOD_MS);

		xRecievedBytes = xMessageBufferReceive(xMessageBuffer
		,&data
		, sizeof(m_data)
		,0 );
		
		for (int i = 0; i < xRecievedBytes; i++)
		{
			for (int j = 0; j < _uplink_payload.len; j+=2)
			{
				_uplink_payload.bytes[j] = data.type >> 8;
				_uplink_payload.bytes[j+1] = data.type & 0xFF;
			}
		}

		//// Some dummy payload
		//uint16_t hum = 12345; // Dummy humidity
		//int16_t temp = 675; // Dummy temp
		//uint16_t co2_ppm = 1050; // Dummy CO2
//
		//_uplink_payload.bytes[0] = hum >> 8;
		//_uplink_payload.bytes[1] = hum & 0xFF;
		//_uplink_payload.bytes[2] = temp >> 8;
		//_uplink_payload.bytes[3] = temp & 0xFF;
		//_uplink_payload.bytes[4] = co2_ppm >> 8;
		//_uplink_payload.bytes[5] = co2_ppm & 0xFF;

		led_short_puls(led_ST4);  // OPTIONAL
		printf("Upload Message >%s<\n", lora_driver_map_return_code_to_text(lora_driver_sent_upload_message(true, &_uplink_payload)));
	}
	vTaskDelete(NULL);
}
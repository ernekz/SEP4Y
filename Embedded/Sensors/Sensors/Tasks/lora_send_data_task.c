/*
 * lora_handler_task.c
 *
 * Created: 5/9/2019 12:42:56 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void lora_reset();

static lora_payload_t _uplink_payload;

/*
	Task that sends data to the server
*/
void lora_send_data_task(void *pvParameters)
{
	m_data data;
	size_t xRecievedBytes;
	

	lora_reset();

	_uplink_payload.len = 4;
	_uplink_payload.port_no = 2;


	while (1)
	{
		xSemaphoreTake(xSemaphore_view_data, portMAX_DELAY);
		
		m_print("\nData Sending Task running!\n",xSemaphore_print);
		
		vTaskDelay(1000/portTICK_PERIOD_MS);

		xRecievedBytes = xMessageBufferReceive(xMessageBuffer
		,&data
		, sizeof(m_data)
		,0 );
		
		//for (int i = 0; i < xRecievedBytes; i++)
		//{
			_uplink_payload.bytes[1] = data.type >> 8;
			_uplink_payload.bytes[2] = data.type & 0xFF;
			_uplink_payload.bytes[3] = data.value >> 8;
			_uplink_payload.bytes[4] = data.type & 0xFF;	
			
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Received measurement for sending: type: %d, val: %d\n\n",data.type, data.value);
			vTaskDelay(1);
			xSemaphoreGive(xSemaphore_print);
		//}

		//vTaskDelay()
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
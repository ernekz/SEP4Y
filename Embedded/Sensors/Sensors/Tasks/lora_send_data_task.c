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

	lora_reset();

	_uplink_payload.len = 4;
	_uplink_payload.port_no = 2;


	while (1)
	{
		xSemaphoreTake(xSemaphore_send_data, portMAX_DELAY);

		vTaskDelay(1000/portTICK_PERIOD_MS);

		if (xQueueReceive(xQueue, &(data), 0) != pdTRUE)
		{
			m_print("Unable to receive data from queue!\n",xSemaphore_print);
		}
		else 
		{	
			xSemaphoreTake(xSemaphore_print,portMAX_DELAY);
			printf("Received measurement for sending: type: %d, val: %d\n\n",data.type, data.value);
			xSemaphoreGive(xSemaphore_print);
			
			_uplink_payload.bytes[0] = data.type >> 8;
			_uplink_payload.bytes[1] = data.type & 0xFF;
			_uplink_payload.bytes[2] = data.value >> 8;
			_uplink_payload.bytes[3] = data.value & 0xFF;

			led_short_puls(led_ST4);  
			printf("Upload Message >%s<\n", lora_driver_map_return_code_to_text(lora_driver_sent_upload_message(true, &_uplink_payload)));
		}
	}
	vTaskDelete(NULL);
}
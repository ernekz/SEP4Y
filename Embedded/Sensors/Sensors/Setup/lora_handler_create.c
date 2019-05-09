/*
 * lora_handler_task.c
 *
 * Created: 5/8/2019 2:05:37 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void lora_handler_task( void *pvParameters );

/*
	This method creates a task that sends data to the server
*/
void lora_handler_create(UBaseType_t lora_handler_task_priority)
{
	xTaskCreate(
	lora_handler_task
	,  (const portCHAR *)"LRHand"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  lora_handler_task_priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}



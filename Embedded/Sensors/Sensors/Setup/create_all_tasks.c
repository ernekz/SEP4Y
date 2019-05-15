/*
 * lora_handler_task.c
 *
 * Created: 5/8/2019 2:05:37 PM
 *  Author: drags
 */ 

#include "../Headers/m_lora_includes.h"

void lora_handler_task( void *pvParameters );
void measure_temp_task(void *pvParameters);
void print_measuremenets_task(void *pvParameters);
void measure_co2_task(void *pvParameters);

void lora_send_data_task(void *pvParameters);
/*
	This method creates all the tasks
*/

void create_all_tasks(UBaseType_t lora_reset_task_priority)
{
	xTaskCreate(
	lora_send_data_task
	,  (const portCHAR *)"LRHand"  
	,  configMINIMAL_STACK_SIZE+200  
	,  NULL
	,  lora_reset_task_priority  
	,  NULL );
	
	xTaskCreate(
	measure_temp_task
	, "Measure Temp Task"
	, configMINIMAL_STACK_SIZE
	, NULL
	, ( tskIDLE_PRIORITY )
	, NULL );
	
	xTaskCreate(
	measure_co2_task
	, "Measure CO2 Task"
	, configMINIMAL_STACK_SIZE
	, NULL
	, ( tskIDLE_PRIORITY )
	, NULL );
}



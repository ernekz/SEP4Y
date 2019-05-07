#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <mh_z19.h>
#include <ihal.h>
#include <hcSr501.h>
#include <stdio_driver.h>

void my_co2_call_back(uint16_t ppm)
{
	printf("CO2 level: %d\n",ppm);
}


int main(void)
{
	stdioCreate(0);
	sei();
	mh_z19_create(ser_USART3, my_co2_call_back); 
	
	uint16_t ppm;
	mh_z19_return_code_t rc;
	
	while (1)
	{
		rc = mh_z19_take_meassuring();
	if (rc != MHZ19_OK)
	{
		printf("Something went wrong");
	}
	_delay_ms(500);
	}
	
}


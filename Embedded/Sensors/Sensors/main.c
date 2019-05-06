#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <mh_z19.h>
#include <ihal.h>
#include <hcSr501.h>
#include <stdio_driver.h>


hcSr501_p hcSr501Inst = NULL;

int main(void)
{
	stdioCreate(0);
	sei();
	hcSr501Inst = hcSr501Create(&PORTE, PE5);
	
	if ( NULL != hcSr501Inst )
	{
		printf("Driver created.\n");
	}else
	{
		printf("Driver not created.\n");
	}
	
	while (1)
	{
		if ( hcSr501IsDetecting(hcSr501Inst) )
		{
			printf("something detected\n");
		}
		else
		{
			printf("nothing detected\n");
		}
		
		_delay_ms(100);
	}
}


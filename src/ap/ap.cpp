#include "ap.h"
#include <pico/multicore.h>

void core1_entry()
{
	imuBegin(50);

	uint32_t start, loop_us;

	start = micros();

	while(1)
	{
		imuUpdate();
		loop_us = micros() - start;
		multicore_fifo_push_blocking(loop_us);
		start = micros();
	}
}

void apInit()
{
	//lcdBegin(_DEF_LCD1);
	//lcdBegin(_DEF_LCD2);
	
 
	//uartOpen(_DEF_UART1, 38400);
	//cliOpen(_DEF_UART1, 38400);

	multicore_launch_core1(core1_entry);
	//imuBegin(50);
}


void apMain()
{
	uint32_t pre_time = millis();
	uint32_t loop_us = 0;

	float *rpy;

	while(1)	
	{
		//printf("Hello, world!\n");
		//printf("%X\n", uartRead(_DEF_UART1));
		
		//lcdPrintf(_DEF_LCD1, 0, 0, WHITE, "Hello, world!");
		//lcdUpdateFrame(_DEF_LCD1);
		if (millis() - pre_time >= 500)
		{
			ledToggle(_DEF_LED1);
			
			if (multicore_fifo_rvalid())
			{
				loop_us = multicore_fifo_pop_blocking();
				printf("%ld\n", loop_us);
			}
			
			pre_time = millis();
		}

		//imuUpdate();
		//rpy = imuGetRPY();
		//printf("%d, %d, %d\n", (int)rpy[0], (int)rpy[1], (int)rpy[2]);

		//cliMain();
	}
}
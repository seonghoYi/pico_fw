#include "ap.h"




void apInit()
{
	lcdBegin(_DEF_LCD1);
	//lcdBegin(_DEF_LCD2);
	
 
	//uartOpen(_DEF_UART1, 38400);
	cliOpen(_DEF_UART1, 38400);
}


void apMain()
{
	uint32_t pre_time = millis();

	while(1)	
	{
		//printf("Hello, world!\n");
		//printf("%X\n", uartRead(_DEF_UART1));
		
		//lcdPrintf(_DEF_LCD1, 0, 0, WHITE, "Hello, world!");
		//lcdUpdateFrame(_DEF_LCD1);
		if (millis() - pre_time >= 500)
		{
			ledToggle(_DEF_LED1);

			pre_time = millis();
		}

		cliMain();
	}
}
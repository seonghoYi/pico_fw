#include "ap.h"


const uint8_t LED_PIN = PICO_DEFAULT_LED_PIN;


void apInit()
{
	/*
	lcdBegin(_DEF_LCD1);
	lcdBegin(_DEF_LCD2);
	*/
 	gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

	uartOpen(_DEF_UART1, 38400);

}


void apMain()
{
	while(1)
	{
		/*
		lcdPrintf(_DEF_LCD1, 0, 0, WHITE, "Hello, world!");
		lcdUpdateFrame(_DEF_LCD1);
		*/
		uartPrintf(_DEF_UART1, "Hello, world!\n");
		gpio_put(LED_PIN, 1);
		delay(250);
		gpio_put(LED_PIN, 0);
		delay(250);
	}
}

#include "ap.h"
#include "hardware/i2c.h"

const uint8_t LED_PIN = PICO_DEFAULT_LED_PIN;


void apInit()
{
	gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

	lcdBegin(_DEF_LCD1);
	//lcdBegin(_DEF_LCD2);
	
 
	uartOpen(_DEF_UART1, 38400);

}


void apMain()
{
	while(1)
	{
		printf("Hello, world!\n");
		delay(250);
		
		gpio_put(LED_PIN, 1);
		delay(250);
		gpio_put(LED_PIN, 0);
		delay(250);
		
		lcdPrintf(_DEF_LCD1, 0, 0, WHITE, "Hello, world!");
		lcdUpdateFrame(_DEF_LCD1);
	}
}
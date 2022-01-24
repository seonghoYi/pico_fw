#include "bsp.h"



void bspInit()
{
  set_sys_clock_khz(133000, true);

  stdio_init_all();
}



uint32_t millis()
{
	return to_ms_since_boot(get_absolute_time());
}

void delay(uint32_t ms)
{
	sleep_ms(ms);
}
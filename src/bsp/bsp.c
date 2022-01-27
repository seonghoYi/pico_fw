#include "bsp.h"



bool bspInit()
{
  bool ret = true;
  set_sys_clock_khz(133000, true);

  stdio_init_all();


  delay(1000);
  return ret;
}



uint32_t millis()
{
	return to_ms_since_boot(get_absolute_time());
}

void delay(uint32_t ms)
{
	sleep_ms(ms);
}
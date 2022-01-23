#include "bsp.h"

#include <hardware/structs/clocks.h>
//#include <hardware/structs/pll.h>



void bspInit()
{
/*

  pll_init(pll_sys, 12, 1500, 6, 2);

  clock_configure(clk_sys,
                  CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                  CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                  125 * MHZ,
                  48 * MHZ);

  //pll_deinit(pll_sys);

  clock_configure(clk_peri,
                  0,
                  CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                  48 * MHZ,
                  48 * MHZ);

*/

}



uint32_t millis()
{
	return 0;
}

void delay(uint32_t ms)
{
	
}
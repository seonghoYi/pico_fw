#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"

#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <hardware/clocks.h>
#include <hardware/pll.h>

bool bspInit();

uint32_t millis();
void delay(uint32_t ms);


#endif /* SRC_BSP_BSP_H_ */

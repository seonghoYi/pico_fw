#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"


#include <hardware/clocks.h>
#include <hardware/pll.h>

void bspInit();

uint32_t millis();
void delay(uint32_t ms);


#endif /* SRC_BSP_BSP_H_ */

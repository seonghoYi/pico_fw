#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


#define _DEF_UART1  0
#define _DEF_UART2  1

#define _DEF_I2C1		0
#define _DEF_I2C2		1

#define _DEF_LCD1		0
#define _DEF_LCD2		1


#define _DEF_OUTPUT	0
#define _DEF_INPUT	1

#define _DEF_LOW		0
#define _DEF_HIGH		1



#define constrain(in,low,high) ((in)<(low)?(low):((in)>(high)?(high):(in)))

#ifndef map
#define map(input, in_min, in_max, out_min, out_max) ((input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#endif


#endif /* SRC_COMMON_DEF_H_ */

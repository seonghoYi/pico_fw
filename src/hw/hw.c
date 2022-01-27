#include "hw.h"




bool hwInit()
{
	bool ret = true;
	ret &= bspInit();
	ret &= uartInit();
	ret &= i2cInit();
	ret &= lcdInit();
	return ret;
}

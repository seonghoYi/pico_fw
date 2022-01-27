#include "hw.h"




bool hwInit()
{
	bool ret = true;
	ret &= bspInit();
	ret &= uartInit();
	ret &= cliInit();
	ret &= i2cInit();
	ret &= lcdInit();
	return ret;
}

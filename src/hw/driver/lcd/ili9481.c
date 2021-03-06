#include "lcd/ili9481.h"
#include "lcd/ili9481_regs.h"





#ifdef _USE_HW_ILI9481

#define NOP		asm volatile("NOP")


void delay_us(uint32_t us)
{
	if (us <= 0)
	{
		return;
	}

	for(int i = 0; i < us * 20; i++)
	{
		NOP;
	}
}




typedef struct
{
	GPIO_TypeDef *port;
	uint32_t 			pin;
	uint8_t 			mode;
	GPIO_PinState on_state;
	GPIO_PinState off_state;
	bool 					init_value;
} gpio_tbl_t;


const gpio_tbl_t gpio_tbl[ILI9481_GPIO_MAX_CH]=
{
		{GPIOA, GPIO_PIN_0, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_LOW},
		{GPIOA, GPIO_PIN_1, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_LOW},
		{GPIOA, GPIO_PIN_4, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_LOW},
		{GPIOB, GPIO_PIN_0, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_LOW},
		{GPIOC, GPIO_PIN_1, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_LOW},
		{GPIOA, GPIO_PIN_9, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOC, GPIO_PIN_7, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOA, GPIO_PIN_10, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOB, GPIO_PIN_3, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOB, GPIO_PIN_5, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOB, GPIO_PIN_4, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOB, GPIO_PIN_10, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
		{GPIOA, GPIO_PIN_8, _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET, _DEF_LOW},
};




bool gpioPinMode(uint8_t ch, uint8_t mode)
{
	bool ret = true;


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if (ch >= ILI9481_GPIO_MAX_CH)
	{
		return false;
	}


	switch(mode)
	{
	case _DEF_INPUT:
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		break;
	case _DEF_OUTPUT:
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		break;
	}

  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = gpio_tbl[ch].pin;

  HAL_GPIO_Init(gpio_tbl[ch].port, &GPIO_InitStruct);

  return ret;
}


void gpioPinWrite(uint8_t ch, bool value)
{
	if (ch >= ILI9481_GPIO_MAX_CH)
	{
		return;
	}

	if(value)
	{
		HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].on_state);
	}
	else
	{
		HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].off_state);
	}
}



bool gpioPinRead(uint8_t ch)
{
	bool ret = false;

	if (ch >= ILI9481_GPIO_MAX_CH)
	{
		return false;
	}

	if (HAL_GPIO_ReadPin(gpio_tbl[ch].port, gpio_tbl[ch].pin) == gpio_tbl[ch].on_state)
	{
		ret = true;
	}
	return ret;
}




bool ili9481InitGPIO()
{
	bool ret = true;


	for(int i = 0; i < ILI9481_GPIO_MAX_CH; i++)
	{
		ret &= gpioPinMode(i, gpio_tbl[i].mode);
		gpioPinWrite(i, gpio_tbl[i].init_value);
	}

	return ret;
}


bool ili9481BusMode(uint8_t mode)
{
	bool ret = true;

	for(int i = _DEF_ILI9481_D0; i < ILI9481_GPIO_MAX_CH; i++)
	{
		ret &= gpioPinMode(i, mode);
	}

	return ret;
}

void ili9481WriteData(uint8_t data);
void ili9481WriteCommand(uint8_t com);
uint8_t ili9481ReadData(void);
bool ili9481Reset();
bool ili9481SetAddrWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);


void ili9481SetPixel(uint32_t x, uint32_t y);


uint16_t ili9481ReadID(void)
{
	uint16_t ret, high = 0;
	uint8_t low = 0;

	gpioPinWrite(_DEF_ILI9481_CS, _DEF_HIGH);


	ili9481WriteCommand(ILI9481_COM_DEVICE_CODE_READ);
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;
	high = ili9481ReadData();
	low = ili9481ReadData();
	ret = (high << 8) | low;

	gpioPinWrite(_DEF_ILI9481_CS, _DEF_LOW);

	return ret;
}



bool ili9481Init()
{
	bool ret = true;

	ret &= ili9481InitGPIO();
	ret &= ili9481Reset();

	ili9481ReadID();

	for (int i = 0; i < ILI9481_WIDTH; i++)
	{
		ili9481SetPixel(i, 200);
	}



	return ret;
}



bool ili9481DriverInit(lcd_driver_t *lcd_driver)
{
	bool ret = true;
	lcd_driver->init 					= ili9481Init;
	lcd_driver->reset 				= ili9481Reset;
	lcd_driver->setWindow 		= ili9481SetAddrWindow;
	lcd_driver->getWidth;
	lcd_driver->getHeight;
	lcd_driver->setCallBack;
	lcd_driver->sendbuffer;

	return ret;
}



bool ili9481Reset()
{
	bool ret = true;
	gpioPinWrite(_DEF_ILI9481_CS, _DEF_LOW);
	delay(100);
	gpioPinWrite(_DEF_ILI9481_RST, _DEF_HIGH);
	delay(100);
	gpioPinWrite(_DEF_ILI9481_RST, _DEF_LOW);
	gpioPinWrite(_DEF_ILI9481_RS, _DEF_LOW);
	gpioPinWrite(_DEF_ILI9481_RD, _DEF_LOW);
	gpioPinWrite(_DEF_ILI9481_WR, _DEF_LOW);

	gpioPinWrite(_DEF_ILI9481_CS, _DEF_HIGH);


	ili9481WriteCommand(ILI9481_COM_EXIT_SLEEP_MODE);
	delay(20);

	ili9481WriteCommand(ILI9481_COM_POWER_SETTING);
	ili9481WriteData(0x07);
	ili9481WriteData(0x42);
	ili9481WriteData(0x18);

	ili9481WriteCommand(ILI9481_COM_VCOM_CONTROL);
	ili9481WriteData(0x00);
	ili9481WriteData(0x07);
	ili9481WriteData(0x10);


	ili9481WriteCommand(ILI9481_COM_POWER_SET_FOR_NORMAL_MODE);
	ili9481WriteData(0x01);
	ili9481WriteData(0x02);


	ili9481WriteCommand(ILI9481_COM_PANEL_DRIVING_SETTING);
	ili9481WriteData(0x10);
	ili9481WriteData(0x3B);
	ili9481WriteData(0x00);
	ili9481WriteData(0x02);
	ili9481WriteData(0x11);


	ili9481WriteCommand(ILI9481_COM_FRAME_RATE_INVERSION_CONTROL);
	ili9481WriteData(0x03);


	ili9481WriteCommand(ILI9481_COM_GAMMA_SETTING);
	ili9481WriteData(0x00);
	ili9481WriteData(0x32);
	ili9481WriteData(0x36);
	ili9481WriteData(0x45);
	ili9481WriteData(0x06);
	ili9481WriteData(0x16);
	ili9481WriteData(0x37);
	ili9481WriteData(0x75);
	ili9481WriteData(0x77);
	ili9481WriteData(0x54);
	ili9481WriteData(0x0C);
	ili9481WriteData(0x00);

	ili9481WriteCommand(ILI9481_COM_SET_ADDRESS_MODE);
	ili9481WriteData(0x0A);

	ili9481WriteCommand(ILI9481_COM_SET_PIXEL_FORMAT);
	ili9481WriteData(0x55);


	ili9481WriteCommand(ILI9481_COM_GAMMA_SETTING);
	ili9481WriteData(0x00);
	ili9481WriteData(0x32);
	ili9481WriteData(0x36);

	ili9481WriteCommand(ILI9481_COM_SET_COLUMN_ADDRESS);
	ili9481WriteData(0x00);
	ili9481WriteData(0x00);
	ili9481WriteData(0x01);
	ili9481WriteData(0x3F);


	ili9481WriteCommand(ILI9481_COM_SET_PAGE_ADDRESS);
	ili9481WriteData(0x00);
	ili9481WriteData(0x00);
	ili9481WriteData(0x01);
	ili9481WriteData(0xE0);

	delay(120);


	ili9481WriteCommand(ILI9481_COM_SET_DISPLAY_ON);

	gpioPinWrite(_DEF_ILI9481_CS, _DEF_LOW);

	return ret;
}


void ili9481WriteData(uint8_t data)
{
	gpioPinWrite(_DEF_ILI9481_RS, _DEF_LOW);


	ili9481BusMode(_DEF_OUTPUT);
	gpioPinWrite(_DEF_ILI9481_D0, data & 0x0001);
	gpioPinWrite(_DEF_ILI9481_D1, data & 0x0002);
	gpioPinWrite(_DEF_ILI9481_D2, data & 0x0004);
	gpioPinWrite(_DEF_ILI9481_D3, data & 0x0008);
	gpioPinWrite(_DEF_ILI9481_D4, data & 0x0010);
	gpioPinWrite(_DEF_ILI9481_D5, data & 0x0020);
	gpioPinWrite(_DEF_ILI9481_D6, data & 0x0040);
	gpioPinWrite(_DEF_ILI9481_D7, data & 0x0080);

	gpioPinWrite(_DEF_ILI9481_WR, _DEF_HIGH);
	delay_us(1);
	gpioPinWrite(_DEF_ILI9481_WR, _DEF_LOW);
}


uint8_t ili9481ReadData()
{
	uint8_t ret = 0;

	gpioPinWrite(_DEF_ILI9481_RS, _DEF_LOW);

	gpioPinWrite(_DEF_ILI9481_RD, _DEF_HIGH);
	delay_us(1);


	ili9481BusMode(_DEF_INPUT);
	ret |= gpioPinRead(_DEF_ILI9481_D0) << 0x0000;
	ret |= gpioPinRead(_DEF_ILI9481_D1) << 0x0001;
	ret |= gpioPinRead(_DEF_ILI9481_D2) << 0x0002;
	ret |= gpioPinRead(_DEF_ILI9481_D3) << 0x0003;
	ret |= gpioPinRead(_DEF_ILI9481_D4) << 0x0004;
	ret |= gpioPinRead(_DEF_ILI9481_D5) << 0x0005;
	ret |= gpioPinRead(_DEF_ILI9481_D6) << 0x0006;
	ret |= gpioPinRead(_DEF_ILI9481_D7) << 0x0007;


	gpioPinWrite(_DEF_ILI9481_RD, _DEF_LOW);

	return ret;
}


void ili9481WriteCommand(uint8_t com)
{
	gpioPinWrite(_DEF_ILI9481_RS, _DEF_HIGH);


	ili9481BusMode(_DEF_OUTPUT);
	gpioPinWrite(_DEF_ILI9481_D0, com & 0x0001);
	gpioPinWrite(_DEF_ILI9481_D1, com & 0x0002);
	gpioPinWrite(_DEF_ILI9481_D2, com & 0x0004);
	gpioPinWrite(_DEF_ILI9481_D3, com & 0x0008);
	gpioPinWrite(_DEF_ILI9481_D4, com & 0x0010);
	gpioPinWrite(_DEF_ILI9481_D5, com & 0x0020);
	gpioPinWrite(_DEF_ILI9481_D6, com & 0x0040);
	gpioPinWrite(_DEF_ILI9481_D7, com & 0x0080);

	gpioPinWrite(_DEF_ILI9481_WR, _DEF_HIGH);
	delay_us(1);
	gpioPinWrite(_DEF_ILI9481_WR, _DEF_LOW);
}


bool ili9481SetAddrWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	ili9481WriteCommand(ILI9481_COM_SET_COLUMN_ADDRESS);
	ili9481WriteData(x >> 8);
	ili9481WriteData(x & 0xFF);
	ili9481WriteData((x + w - 1) >> 8);
	ili9481WriteData((x + w - 1) & 0xFF);
	ili9481WriteCommand(ILI9481_COM_SET_PAGE_ADDRESS);
	ili9481WriteData(y >> 8);
	ili9481WriteData(y & 0xFF);
	ili9481WriteData((y + h - 1) >> 8);
	ili9481WriteData((y + h - 1) & 0xFF);
	ili9481WriteCommand(ILI9481_COM_WRITE_MEMORY_START);
	return true;
}


void ili9481SetPixel(uint32_t x, uint32_t y)
{
	gpioPinWrite(_DEF_ILI9481_CS, _DEF_HIGH);
	ili9481SetAddrWindow(x, y, 1, 1);
	ili9481WriteData(0x00);
	ili9481WriteData(0x00);
	gpioPinWrite(_DEF_ILI9481_CS, _DEF_LOW);
}












#endif

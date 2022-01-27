#include "i2c.h"
#include "hardware/i2c.h"

#ifdef _USE_HW_I2C


typedef struct
{
	bool is_init;
	i2c_inst_t *p_hi2c;
} i2c_tbl_t;


i2c_tbl_t i2c_tbl[I2C_CH_MAX];



bool i2cInit()
{
	for(int i = 0; i < I2C_CH_MAX; i++)
	{
		i2c_tbl[i].is_init = false;
		i2c_tbl[i].p_hi2c 	 = NULL;
	}

	return true;
}

bool i2cBegin(uint8_t ch, uint32_t freq_khz)
{
	bool ret = false;

	switch(ch)
	{
		case _DEF_I2C1:
			i2c_tbl[ch].p_hi2c = i2c0;
			i2c_init(i2c_tbl[_DEF_I2C1].p_hi2c, freq_khz * 1000);
			gpio_set_function(0, GPIO_FUNC_I2C);
			gpio_set_function(1, GPIO_FUNC_I2C);

			gpio_pull_up(0);
			gpio_pull_up(1);

			//bi_decl(bi_2pins_with_func(2, 3, GPIO_FUNC_I2C));
    	//bi_decl(bi_program_description("OLED I2C example for the Raspberry Pi Pico"));
			ret = true;
		break;
		default:
		break;
	}

	return ret;
}

uint32_t i2cWrite(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	i2c_inst_t *p_handle = i2c_tbl[ch].p_hi2c;

	if (i2c_write_blocking(p_handle, dev_addr >> 1, p_data, size, false) > 0)
	{
		ret = size;
	}
	return ret;
}

uint32_t i2cRead(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	i2c_inst_t *p_handle = i2c_tbl[ch].p_hi2c;

	if(i2c_read_blocking(p_handle, dev_addr >> 1, p_data, size, false) > 0)
	{
		ret = size;
	}

	return ret;
}

uint32_t i2cMemWrite(uint8_t ch, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	i2c_inst_t *p_handle = i2c_tbl[ch].p_hi2c;

	uint8_t *temp = malloc(size + mem_addr_size);
	
	if (mem_addr_size > 1)
	{
		for(int i = 0; i < mem_addr_size; i++)
		{
			temp[i] = (mem_addr >> 8 * i) & 0xFF;
		}
	}
	else
	{
		temp[0] = mem_addr;
	}

	for (int i = mem_addr_size; i < size + mem_addr_size; i++)
	{
		temp[i] = p_data[i-mem_addr_size];
	}

	if (i2c_write_blocking(p_handle, dev_addr >> 1, temp, size + mem_addr_size, false) > 0)
	{
		ret = size;
	}

	free(temp);

	return ret;
}

uint32_t i2cMemRead(uint8_t ch, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	i2c_inst_t *p_handle = i2c_tbl[ch].p_hi2c;

	if(i2c_write_blocking(p_handle, dev_addr >> 1, (uint8_t *)&mem_addr, mem_addr_size, true) > 0)
	{
		if(i2c_read_blocking(p_handle, dev_addr >> 1, p_data, size, false) > 0)
		{
			ret = size;
		}
	}

	return ret;
}



#endif

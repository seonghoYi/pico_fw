#include "i2c.h"
#include "hardware/i2c.h"

#ifdef _USE_HW_I2C




typedef struct
{
	bool is_init;


	I2C_HandleTypeDef *p_hi2c;
} i2c_tbl_t;


i2c_tbl_t i2c_tbl[I2C_CH_MAX];



bool i2cInit()
{
	for(int i = 0; i < I2C_CH_MAX; i++)
	{
		i2c_tbl[i].is_init = false;
		i2c_tbl[i].p_hi2c = NULL;
	}

	return true;
}

bool i2cBegin(uint8_t ch, uint32_t freq_khz)
{
	bool ret = false;

	i2c_tbl_t *p_i2c = &i2c_tbl[ch];


	switch(ch)
	{
		case _DEF_I2C1:
			p_i2c->p_hi2c = &hi2c1;
			p_i2c->p_hi2c->Instance = I2C1;
			p_i2c->p_hi2c->Init.ClockSpeed = freq_khz * 1000;
			p_i2c->p_hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
			p_i2c->p_hi2c->Init.OwnAddress1 = 0;
			p_i2c->p_hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
			p_i2c->p_hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
			p_i2c->p_hi2c->Init.OwnAddress2 = 0;
			p_i2c->p_hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
			p_i2c->p_hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


			HAL_I2C_DeInit(&hi2c1);
		  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
		  {
		    Error_Handler();
		  }

		break;
		default:
		break;
	}

	return ret;
}

uint32_t i2cWrite(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

	if(HAL_I2C_Master_Transmit(p_handle, dev_addr, p_data, size, 100) == HAL_OK)
	{
		ret = size;
	}
	return ret;
}

uint32_t i2cRead(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

	if(HAL_I2C_Master_Receive(p_handle, dev_addr, p_data, size, 100) == HAL_OK)
	{
		ret = size;
	}

	return ret;
}

uint32_t i2cMemWrite(uint8_t ch, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

	if(HAL_I2C_Mem_Write(p_handle, dev_addr, mem_addr, mem_addr_size, p_data, size, 100) == HAL_OK)
	{
		ret = size;
	}
	return ret;
}

uint32_t i2cMemRead(uint8_t ch, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *p_data, uint16_t size)
{
	uint32_t ret = 0;

	I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

	if(HAL_I2C_Mem_Read(p_handle, dev_addr, mem_addr, mem_addr_size, p_data, size, 100) == HAL_OK)
	{
		ret = size;
	}
	return ret;
}



#endif

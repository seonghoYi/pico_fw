#include "imu/mpu6050.h"
#include "imu/mpu6050_regs.h"
#include "i2c.h"

#include "cli.h"


#ifdef _USE_HW_MPU6050


#define MPU6050_I2C_ADDRESS 0x68 << 1

static void cliMpu6050(cli_args_t *args);

bool mpu6050Init()
{
  bool ret = true;


  cliAdd("MPU6050", cliMpu6050);

  return ret;
}



cMPU6050::cMPU6050()
{
  b_connected = false;
  i2c_addr = MPU6050_I2C_ADDRESS;
}

bool cMPU6050::init()
{
  bool ret = true;
  uint8_t data = 0;

  ret &= i2cBegin(_DEF_I2C2, 400);
  
  //mpu6050 reset
  ret &= i2cMemWrite(_DEF_I2C2, i2c_addr, MPU6050_PWR_MGMT_1, 1, MPU6050_RESET);
  delay(100);

  //mpu6050 wakeup
  ret &= i2cMemWrite(_DEF_I2C2, i2c_addr, MPU6050_PWR_MGMT_1, 1, 0x00);

  //mpu6050 acc 2g
  ret &= i2cMemWrite(_DEF_I2C2, i2c_addr, MPU6050_ACCEL_CONFIG, 1, MPU6050_ACCEL_FSR2 << 3); 

  //mpu6050 gyro 2000
  ret &= i2cMemWrite(_DEF_I2C2, i2c_addr, MPU6050_GYRO_CONFIG, 1, MPU6050_GYRO_FSR2000 << 3);

  //mpu6050 config DLPF ~20Hz
  ret &= i2cMemRead(_DEF_I2C2, i2c_addr, MPU6050_CONFIG, 1, data);
  data |= MPU6050_CONFIG_DLFP4;
  ret &= i2cMemWrite(_DEF_I2C2, i2c_addr, MPU6050_CONFIG, 1, data);

  return ret;
}

bool cMPU6050::begin()
{
  bool ret = true;
  ret &= init();
  accInit();
  gyroInit();

  if (ret)
  {
    b_connected = true;
    return b_connected;
  }
  else
  {
    return ret;
  }
}


void cMPU6050::accInit()
{
  for (int axis = 0; axis < 3; axis++)
  {
    accRaw[axis] = 0;
    accData[axis] = 0;
  }
}

void cMPU6050::getAccRaw()
{
  int16_t x;
  int16_t y;
  int16_t z;

  uint8_t raw[6];

  if (b_connected == true)
  {
    i2cMemReads(_DEF_I2C2, MPU6050_I2C_ADDRESS, MPU6050_ACCEL_XOUT_H, 1, raw, 6);

    x = (((int16_t)raw[0]) << 8) | raw[1];
    y = (((int16_t)raw[2]) << 8) | raw[3];
    z = (((int16_t)raw[4]) << 8) | raw[5];


    accRaw[0] = x;
    accRaw[1] = y;
    accRaw[2] = z;

    accData[0] = x;
    accData[1] = y;
    accData[2] = z;
  }
  
}

void cMPU6050::gyroInit()
{
  for (int axis = 0; axis < 3; axis++)
  {
    gyroRaw[axis] = 0;
    gyroData[axis] = 0;
  }
}

void cMPU6050::getGyroRaw()
{
  int16_t x;
  int16_t y;
  int16_t z;

  uint8_t raw[6];

  if (b_connected == true)
  {
    i2cMemReads(_DEF_I2C2, MPU6050_I2C_ADDRESS, MPU6050_GYRO_XOUT_H, 1, raw, 6);

    x = (((int16_t)raw[0]) << 8) | raw[1];
    y = (((int16_t)raw[2]) << 8) | raw[3];
    z = (((int16_t)raw[4]) << 8) | raw[5];


    gyroRaw[0] = x;
    gyroRaw[1] = y;
    gyroRaw[2] = z;

    gyroData[0] = x;
    gyroData[1] = y;
    gyroData[2] = z;
  }
}


#ifdef _USE_HW_CLI

void cliMpu6050(cli_args_t *args)
{
  bool ret = true;
  static cMPU6050 mpu;

  if(args->argc == 1)
  {
    if(args->isStr(0, "begin"))
    {
      ret = mpu.begin();
      if(ret == false)
      {
        cliPrintf("error\n");
      }
      else
      {
        cliPrintf("success\n");
      }
    }
    else if(args->isStr(0, "getraw"))
    {
      mpu.getAccRaw();
      mpu.getGyroRaw();

      cliPrintf("Acc x: %d, y: %d, z: %d\n", mpu.accData[0], mpu.accData[1], mpu.accData[2]);
      cliPrintf("Gyr x: %d, y: %d, z: %d\n", mpu.gyroData[0], mpu.gyroData[1], mpu.gyroData[2]);
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }
  

  if(ret == false)
  {
    cliPrintf("mpu6050 begin\n");
  }

}



#endif
#endif
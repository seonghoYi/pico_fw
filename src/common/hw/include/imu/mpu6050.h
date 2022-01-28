#ifndef SRC_COMMON_HW_INCLUDE_IMU_MPU6050_H_
#define SRC_COMMON_HW_INCLUDE_IMU_MPU6050_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#ifdef _USE_HW_MPU6050


bool mpu6050Init(void);


class cMPU6050
{
  public:
    bool b_connected;
    
    
    int16_t accRaw[3];
    int16_t accData[3];
    int16_t gyroRaw[3];
    int16_t gyroData[3];




  public:
    cMPU6050();

    bool begin(void);
    void getGyroRaw(void);
    void getAccRaw(void);

  private:
    uint16_t i2c_addr;

  private:
    bool init(void);
    void accInit(void);
    void gyroInit(void);
};



#endif

#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_HW_INCLUDE_MPU6050_H_ */
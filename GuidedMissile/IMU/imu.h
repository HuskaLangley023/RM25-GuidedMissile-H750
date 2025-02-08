/**
******************************************************************************
* @file : imu.h
* @author : Albert Wang
* @brief : None
* @date : 2024/1/24
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_IMU_H
#define RM24_GUIDEDMISSILE_H750_IMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

void imuInit(void);

void imuHandle(void);

extern float bmi_gyro[3], bmi_accel[3], temp;
extern float missile_ax, missile_ay, missile_az; // unit: m/s^2
extern float missile_wx, missile_wy, missile_wz; // unit: rad/s
extern float yaw, pitch, roll; // unit: degree
extern float quat[4];

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_IMU_H

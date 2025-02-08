/**
******************************************************************************
* @file : imu.c
* @author : Albert Wang
* @brief : None
* @date : 2024/1/24
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "imu.h"
#include "BMI088driver.h"
#include "MahonyAHRS.h"
#include "arm_math.h"

float bmi_gyro[3], bmi_accel[3], temp;
float missile_ax, missile_ay, missile_az; // unit: m/s^2
float missile_wx, missile_wy, missile_wz; // unit: rad/s
float yaw, pitch, roll; // unit: degree
float quat[4] = {1.0f, 0.0f, 0.0f, 0.0f};

void quat2Angle(float quat_[4], float *yaw_, float *pitch_, float *roll_) {
    *yaw_ = atan2f(2.0f * (quat_[0] * quat_[3] + quat_[1] * quat_[2]), 2.0f * (quat_[0] * quat_[0] + quat_[1] * quat_[1]) - 1.0f) * 57.3f;
    *pitch_ = asinf(-2.0f * (quat_[1] * quat_[3] - quat_[0] * quat_[2])) * 57.3f;
    *roll_ = -atan2f(2.0f * (quat_[0] * quat_[1] + quat_[2] * quat_[3]), 2.0f * (quat_[0] * quat_[0] + quat_[3] * quat_[3]) - 1.0f) * 57.3f;
}

void imuInit() {
    BMI088_init();
}

void imuHandle() {
    BMI088_read(bmi_gyro, bmi_accel, &temp);

    missile_ax = -bmi_accel[1];
    missile_ay = bmi_accel[0];
    missile_az = bmi_accel[2];

    missile_wx = -bmi_gyro[1];
    missile_wy = bmi_gyro[0];
    missile_wz = bmi_gyro[2];

    MahonyAHRSupdateIMU(quat, missile_wx, missile_wy, missile_wz, missile_ax, missile_ay, missile_az, 1000.0f);
    quat2Angle(quat, &yaw, &pitch, &roll);
}

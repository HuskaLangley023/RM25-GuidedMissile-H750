/**
******************************************************************************
* @file : flight_control.cpp
* @author : Albert Wang
* @brief : None
* @date : 2024/1/20
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "flight_control.h"
#include "light_recognition.h"
#include "imu.h"
#include "BMI088driver.h"
#include "as6500.h"

extern Encoder encoder_l;
extern Encoder encoder_r;

PID tx_control_pid(0.2, 0, 0.2, 0, 45);
PID fy_control_pid(20, 0, 0, 0, 45);
PID fz_control_pid(20, 0, 0, 0, 45);

FlightControl::FlightControl(Servo *rudder1, Servo *rudder2, Servo *rudder3, Servo *rudder4)
        : rudder1_(rudder1),
          rudder2_(rudder2),
          rudder3_(rudder3),
          rudder4_(rudder4),
          tx_control_pid_(tx_control_pid),
          fy_control_pid_(fy_control_pid),
          fz_control_pid_(fz_control_pid) {}

void FlightControl::init(void) {
    rudder1_->init();
    rudder2_->init();
    rudder3_->init();
    rudder4_->init();
    launch_flag_ = false;
    launch_time_ = 0;
    flight_time_ = 0;
    downward_first_enter_ = true;
    launch_first_enter_ = true;
}

void FlightControl::handle(void) {

    //TODO 磁传感器实现飞控
    encoder_l.asHandle();
    encoder_r.asHandle();
    //


    rudder_angle_.rudder2_angle = -10;
    rudder_angle_.rudder4_angle = 10;

    BMI088_read(bmi_gyro, bmi_accel, &temp);

    if (bmi_accel[1] > 15) {
        launch_flag_ = 1;
    }
    missile_earth_frame_.euler_angle.pitch = pitch + launch_pitch;
    missile_earth_frame_.euler_angle.roll = roll;
    missile_earth_frame_.euler_angle.yaw = yaw;

    if (launch_flag_) {
        if (launch_first_enter_) {
            launch_time_ = HAL_GetTick();
            launch_first_enter_ = 0;
        }
        if (flight_time_ > 25) {
            imuHandle();
        }

        if (flight_time_ < 1100) {
            state_ = UPWARD;
        } else if (1100 <= flight_time_ && flight_time_ < 1300) {
            state_ = DOWNWARD;
        } else if (1300 <= flight_time_ && flight_time_ < 2000) {
            state_ = FINAL;
        } else if (flight_time_ >= 2000) {
            state_ = STOP;
        }

        if (state_ == UPWARD && flight_time_ > 100) {
            target_body_frame_.y = 0;
            target_body_frame_.z = 0.35;
        } else if (state_ == DOWNWARD) {
            target_body_frame_.y = 0;
            target_body_frame_.z = 0.25;
        } else if (state_ == FINAL) {
            calcLightBodyFrame();
            target_body_frame_.y = light_body_frame_.y;
//            target_body_frame_.z = (float) ((flight_time_ - 1000) / 1000.0f) * light_body_frame_.z;
            target_body_frame_.z = 0;
        } else if (state_ == STOP) {
            rudder1_->stop();
            rudder2_->stop();
            rudder3_->stop();
            rudder4_->stop();
        }
        if (state_ != STOP) {
            calcForce();
            calcRudderAngle();
            flight_time_ = HAL_GetTick() - launch_time_;
        }
    }

    if (state_ != STOP) {
        rudderHandle();
    }
}

void FlightControl::calcMissileEarthFrame(void) {
    missile_earth_frame_.x = launch_velocity_x_ * flight_time_;
    missile_earth_frame_.z = launch_velocity_y_ * flight_time_ + 0.5 * gravity * powf(flight_time_, 2);
    missile_earth_frame_.vx = launch_velocity_x_;
    missile_earth_frame_.vz = launch_velocity_y_ * sinf(launch_pitch) + gravity * flight_time_;
}

void FlightControl::calcLightBodyFrame(void) {
    light_body_frame_.y = 2.0f * circle.cx / WIDTH - 1.0f;
    light_body_frame_.z = -(2.0f * circle.cy / HEIGHT - 1.0f); // circle.cy向下为正
}

void FlightControl::calcForce(void) {
    general_force_.tx = tx_control_pid_.calc(0, missile_earth_frame_.euler_angle.roll);
    general_force_.fy = -fy_control_pid_.calc(0, target_body_frame_.y);
    general_force_.fz = -fz_control_pid_.calc(0, target_body_frame_.z);
}

void FlightControl::calcRudderAngle(void) {
    float fy_weight = 1.0f;
    float fz_weight = 1.0f;
    rudder_angle_.rudder1_angle = -fy_weight * general_force_.fy + general_force_.tx; // rudder_angle在舵面平直时为零点
    rudder_angle_.rudder2_angle = -fz_weight * general_force_.fz + general_force_.tx;
    rudder_angle_.rudder3_angle = fy_weight * general_force_.fy + general_force_.tx;
    rudder_angle_.rudder4_angle = fz_weight * general_force_.fz + general_force_.tx;

    /*
    // 若超限则削减fy或fz 若仅剩tx时仍超限将在后续舵机setTargetAngle处限幅
    while ((abs(rudder_angle_.rudder1_angle) > 40 || abs(rudder_angle_.rudder3_angle) > 40) && fy_weight >= 0.01f) {
        fy_weight -= 0.01f;
        rudder_angle_.rudder1_angle = -fy_weight * general_force_.fy + general_force_.tx;
        rudder_angle_.rudder3_angle = fy_weight * general_force_.fy + general_force_.tx;
    }
    while ((abs(rudder_angle_.rudder2_angle) > 40 || abs(rudder_angle_.rudder4_angle) > 40) && fz_weight >= 0.01f) {
        fz_weight -= 0.01f;
        rudder_angle_.rudder2_angle = -fz_weight * general_force_.fz + general_force_.tx;
        rudder_angle_.rudder4_angle = +fz_weight * general_force_.fz + general_force_.tx;
    }
     */
}

void FlightControl::rudderHandle(void) {
    rudder1_->setTargetAngle(rudder2servo_ud(rudder_angle_.rudder1_angle));
    rudder2_->setTargetAngle(rudder2servo_lr(rudder_angle_.rudder2_angle));
    rudder3_->setTargetAngle(rudder2servo_ud(rudder_angle_.rudder3_angle));
    rudder4_->setTargetAngle(rudder2servo_lr(rudder_angle_.rudder4_angle));
    rudder1_->handle();
    rudder2_->handle();
    rudder3_->handle();
    rudder4_->handle();
}

float FlightControl::rudder2servo_ud(float rudder) {
    return (0.0025f * pow(rudder, 2.0f) + 0.6163f * rudder + 90.0f);
}

float FlightControl::rudder2servo_lr(float rudder) {
    return (0.0023f * pow(rudder, 2.0f) + 0.5918f * rudder + 90.0f);
}

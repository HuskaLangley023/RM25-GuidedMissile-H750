/**
******************************************************************************
* @file : flight_control.h
* @author : Albert Wang
* @brief : None
* @date : 2024/1/20
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_FLIGHT_CONTROL_H
#define RM24_GUIDEDMISSILE_H750_FLIGHT_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"
#include "missile.h"
#include "servo.h"
#include "tim.h"
#include "common/pid.h"

typedef struct {
    float x; // Forward
    float y; // Right
    float z; // Height
    float vx;
    float vy;
    float vz;
    struct {
        float pitch;
        float yaw;
        float roll;
    } euler_angle;
    float wx;
    float wy;
    float wz;
} Coordinate_t;

class FlightControl {
public:
    FlightControl(Servo *rudder1, Servo *rudder2, Servo *rudder3, Servo *rudder4);

    void init(void);

    void handle(void);

    void calcMissileEarthFrame(void);

    void calcLightBodyFrame(void);

    void calcError(void); // 计算与正确轨迹偏差

    void calcForce(void);

    void calcRudderAngle(void);

    void rudderHandle(void);

    static float rudder2servo_ud(float rudder);

    static float rudder2servo_lr(float rudder);


public:
    struct {
        const float x = 26.0f; // Forward
        const float y = 0; // Right
        const float z = 1.0f; // Height
    } light_earth_frame_;

    struct {
        float tx; // Torque
        float ty;
        float tz;
        float fx; // Force
        float fy;
        float fz;
    } general_force_;

    struct {
        float rudder1_angle; // Up
        float rudder2_angle; // Right
        float rudder3_angle; // Down
        float rudder4_angle; // Left
    } rudder_angle_;

    typedef enum State {
        UPWARD,
        DOWNWARD,
        FINAL,
        STOP,
        ERR,
    } State_e;

    Servo *rudder1_, *rudder2_, *rudder3_, *rudder4_;

    Coordinate_t missile_earth_frame_; // 地球系下的飞镖
    Coordinate_t light_body_frame_; // 飞镖系下的绿灯
    Coordinate_t target_body_frame_; // 飞镖系下的目标点
    State_e state_;

    uint8_t launch_flag_;
    uint32_t launch_time_;
    uint32_t flight_time_;
    uint8_t downward_first_enter_;
    uint8_t launch_first_enter_;
    float launch_velocity_x_;
    float launch_velocity_y_;

    PID tx_control_pid_;
    PID fy_control_pid_;
    PID fz_control_pid_;

    const float gravity = -9.81f;
    const float launch_pitch = 35.0f; // 初速度与地面成角(degree)
};

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_FLIGHT_CONTROL_H

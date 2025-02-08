/**
******************************************************************************
* @file : servo.h
* @author : Albert Wang
* @brief : None
* @date : 2024/1/20
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_SERVO_H
#define RM24_GUIDEDMISSILE_H750_SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"

#define INRANGE(NUM, MIN, MAX) \
{\
    if(NUM<MIN){\
        NUM=MIN;\
    }else if(NUM>MAX){\
        NUM=MAX;\
    }\
}

#define AFFINE(BEFORE_MIN, BEFORE_MAX, TARGET_MIN, TARGET_MAX, X)\
(X-BEFORE_MIN)/(float)(BEFORE_MAX - BEFORE_MIN)*(TARGET_MAX - TARGET_MIN)\
+ TARGET_MIN

class Servo {
public:
    Servo(TIM_HandleTypeDef *htim, uint32_t channel, float angle_min, float angle_max, float zero_angle);

    void init();

    void handle();

    void setTargetAngle(float target_angle);

    void stop();

public:
    TIM_HandleTypeDef *htim_;
    uint32_t channel_;
    float angle_min_;
    float angle_max_;
    float zero_angle_;
    float target_angle_;
    float duty_;
    uint8_t stop_flag_;
};

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_SERVO_H

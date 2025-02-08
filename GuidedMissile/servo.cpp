/**
******************************************************************************
* @file : servo.cpp
* @author : Albert Wang
* @brief : None
* @date : 2024/1/20
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "servo.h"

Servo::Servo(TIM_HandleTypeDef *htim, uint32_t channel, float angle_min, float angle_max, float zero_angle)
        : htim_(htim),
          channel_(channel),
          angle_min_(angle_min),
          angle_max_(angle_max),
          zero_angle_(zero_angle){}

void Servo::init() {
    HAL_TIM_Base_Start_IT(htim_);
    HAL_TIM_PWM_Start(htim_, channel_);
    setTargetAngle(90);
    handle();
}

void Servo::handle() {
    duty_ = AFFINE(0, 180, 0.025, 0.125, target_angle_);
    __HAL_TIM_SET_COMPARE(htim_, channel_, htim_->Instance->ARR * duty_);
}

void Servo::setTargetAngle(float target_angle) {
    float angle = target_angle;
    INRANGE(angle, angle_min_, angle_max_);
    target_angle_ = angle + zero_angle_;
    if (stop_flag_) {
        stop_flag_ = 0;
        init();
    }
}

void Servo::stop() {
    if (stop_flag_ == 0) {
        HAL_TIM_PWM_Stop(htim_, channel_);
        stop_flag_ = 1;
    }
}

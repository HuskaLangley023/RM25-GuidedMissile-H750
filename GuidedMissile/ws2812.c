/**
******************************************************************************
* @file : ws2812.c
* @author : Albert Wang
* @brief : None
* @date : 2024/3/6
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "ws2812.h"

uint32_t send_Buf1[NUM1];

void wsHandle(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < 24; i++) {
        send_Buf1[i] = (((wsColor(red, green, blue) << i) & 0X800000) ? WS1 : WS0);
    }

    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *) send_Buf1, NUM1);
}

uint32_t wsColor(uint8_t red, uint8_t green, uint8_t blue) {
    return green << 16 | red << 8 | blue;
}

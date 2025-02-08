/**
******************************************************************************
* @file : ws2812.h
* @author : Albert Wang
* @brief : None
* @date : 2024/3/6
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_WS2812B_H
#define RM24_GUIDEDMISSILE_H750_WS2812B_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"


#define NUM1 (24 + 300)
#define WS1  167
#define WS0  83

extern uint32_t send_Buf1[NUM1];

void wsHandle(uint8_t red, uint8_t green, uint8_t blue);

uint32_t wsColor(uint8_t red, uint8_t green, uint8_t blue);

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_WS2812B_H

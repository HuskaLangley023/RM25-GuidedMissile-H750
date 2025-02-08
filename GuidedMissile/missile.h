/**
******************************************************************************
* @file : missile.h
* @author : Albert Wang
* @brief : None
* @date : 2023/11/19
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef GUIDEDMISSILE_MISSILE_H
#define GUIDEDMISSILE_MISSILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "missile_config.h"
#include "stm32h7xx_hal.h"

void controlInit(void);

void controlLoop(void);

void controlWhileLoop(void);

extern uint8_t image_buf[HEIGHT][WIDTH];
extern uint8_t image[HEIGHT][WIDTH];
extern uint8_t image_compressed[HEIGHT / 2][96];
extern uint32_t tick;

#ifdef __cplusplus
}
#endif

#endif //GUIDEDMISSILE_MISSILE_H

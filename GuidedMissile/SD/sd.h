/**
******************************************************************************
* @file : sd.h
* @author : Albert Wang
* @brief : None
* @date : 2024/4/16
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_SD_H
#define RM24_GUIDEDMISSILE_H750_SD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"

void sdInit(void);

extern uint8_t dir_num;

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_SD_H

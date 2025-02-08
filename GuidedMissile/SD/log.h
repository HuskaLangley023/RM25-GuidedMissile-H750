/**
******************************************************************************
* @file : log.h
* @author : Albert Wang
* @brief : None
* @date : 2024/1/17
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_LOG_H
#define RM24_GUIDEDMISSILE_H750_LOG_H

#include "missile.h"

void logInit(void);

void logHandle(void);

void logStop(void);

extern uint8_t log_stop;

#endif //RM24_GUIDEDMISSILE_H750_LOG_H

/**
  ******************************************************************************
  * @file           : missile_config.h
  * @author         : Albert Wang
  * @brief          : None
  * @date           : 2023/11/25
  ******************************************************************************
  * Copyright (c) 2023 Team JiaoLong-SJTU
  * All rights reserved.
  ******************************************************************************
  */

#ifndef GUIDEDMISSILE_CONFIG_H
#define GUIDEDMISSILE_CONFIG_H

#define HEIGHT  120
#define WIDTH  188

// #define DCMI_CAMERA
#define IMU
#define USB_SHOW
#define CV_FIND_CIRCLE
#define FLIGHT_CONTROL
//磁编码器
#define ENCODER
#ifdef ENCODER
#define ENCODER_LR
// #define ENCODER_UP
#endif

// #define SD
#ifdef SD
#define SD_LOG
#define SD_PIC
#endif

#endif //GUIDEDMISSILE_CONFIG_H

/**
  ******************************************************************************
  * @file           : callback.cpp
  * @author         : Albert Wang
  * @brief          : None
  * @date           : 2023/11/19
  ******************************************************************************
  * Copyright (c) 2023 Team JiaoLong-SJTU
  * All rights reserved.
  ******************************************************************************
  */

#include "callback.h"
#include "tim.h"
#include "missile.h"
#include "string.h"
#include "usb_show.h"
#include "log.h"
#include "ws2812.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim6) { // 1ms
        controlLoop();
    }
}

#ifdef DCMI_CAMERA
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
    HAL_DCMI_Stop(hdcmi);
    SCB_InvalidateDCache_by_Addr(image_buf, HEIGHT * WIDTH);
    memcpy(image, image_buf, HEIGHT * WIDTH);
}
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY_Pin) {
        if (!HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)) {
            usb_stop = 1; // Stop MATLAB
            log_stop = 1; // Stop SD
            wsHandle(0, 0, 10);
        }
    }
}

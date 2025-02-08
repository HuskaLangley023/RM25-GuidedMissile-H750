/**
******************************************************************************
* @file : missile.cpp
* @author : Albert Wang
* @brief : None
* @date : 2023/11/19
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "missile.h"
#include "test_img.h"
#include "tim.h"
#include "dcmi.h"
#include "mt9v034_driver.h"
#include "light_recognition.h"
#include "usb_show.h"
#include "sd.h"
#include "bmp.h"
#include "log.h"
#include "flight_control.h"
#include "servo.h"
#include "imu.h"
#include "ws2812.h"
#include "as6500.h"

uint8_t image_buf[HEIGHT][WIDTH];
uint8_t image[HEIGHT][WIDTH];
uint8_t image_compressed[HEIGHT / 2][96]; // fatfs使用dma, 每行需要4bytes对齐

uint32_t tick;

Servo rudder1(&htim1, TIM_CHANNEL_1, 66, 117, 3);
Servo rudder2(&htim1, TIM_CHANNEL_2, 70, 124, 3);
Servo rudder3(&htim1, TIM_CHANNEL_3, 66, 117, -7);
Servo rudder4(&htim1, TIM_CHANNEL_4, 70, 124, -7);

FlightControl flight_control(&rudder1, &rudder2, &rudder3, &rudder4);

void controlInit(void) {
    HAL_Delay(1);
    wsHandle(10, 0, 0);
#ifdef IMU
    imuInit();
#endif

#ifdef FLIGHT_CONTROL
    flight_control.init();
#endif

#ifdef ENCODER
    as6500init();
#endif

#ifdef SD
    sdInit();
#endif

#ifdef SD_LOG
    logInit();
#endif

#ifdef SD_PIC
    bmpInit();
#endif

#ifdef DCMI_CAMERA
    mt9Init();
#else
    memcpy(image, gray_img, HEIGHT*WIDTH);
#endif

    HAL_TIM_Base_Start_IT(&htim6);
}

void controlLoop(void) {
    // Global Begin
    tick++;
    // Global End

#ifdef DCMI_CAMERA
    if (tick % 10 == 0) {
        __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME);
        HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t) image_buf, HEIGHT * WIDTH);
    }
#endif

#ifdef FLIGHT_CONTROL
    flight_control.handle();
#endif

#if  defined(USB_SHOW) || defined(SD_PIC)
    if (tick % 10 == 5) {
        for (uint8_t i = 0; i < HEIGHT / 2; i++) {
            for (uint8_t j = 0; j < WIDTH / 2; j++) {
                image_compressed[i][j] = image[i * 2][j * 2];
            }
        }
    }
#endif

#ifdef USB_SHOW
    if (tick % 100 == 50) {
        usbHandle();
    }
#endif

#ifdef SD_LOG
    if (flight_control.state_ != FlightControl::STOP && flight_control.launch_flag_) {
        logHandle();
    }
#endif

#ifdef SD_PIC
    if (flight_control.state_ != FlightControl::STOP && flight_control.flight_time_ >= 1300 &&
        flight_control.flight_time_ % 40 == 0) {
        bmpCache();
    } else if (flight_control.state_ == FlightControl::STOP) {
        static uint8_t bmp_first_enter;
        if (!bmp_first_enter) {
            bmpSave();
        }
        bmp_first_enter = 1;
    }
#endif

    if (tick % 500 == 0) {
        if (flight_control.state_ != FlightControl::STOP) {
            static uint8_t toggle = 1;
            if (toggle) {
                wsHandle(0, 10, 0);
            } else {
                wsHandle(0, 0, 0);
            }
            toggle = !toggle;
        } else {
            wsHandle(3, 3, 3);
        }
    }
}

void controlWhileLoop(void) {
#ifdef CV_FIND_CIRCLE
    if (flight_control.state_ == FlightControl::FINAL) {
        cvHandle();
    }
#endif
}

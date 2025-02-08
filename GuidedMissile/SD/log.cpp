/**
******************************************************************************
* @file : log.cpp
* @author : Albert Wang
* @brief : None
* @date : 2024/1/17
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "log.h"
#include "sd.h"
#include "fatfs.h"
#include "light_recognition.h"
#include "flight_control.h"

FIL log_file;

extern FlightControl flight_control;

uint8_t log_stop;

void logInit(void) {
    char file_path[16];
    sprintf(file_path, "0:/%d/log.csv", dir_num);

    f_open(&log_file, file_path, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    f_lseek(&log_file, f_size(&log_file));
    f_printf(&log_file, "TIME,%d,EVENT,Log file created\n", tick);
    f_lseek(&log_file, f_size(&log_file));
    f_printf(&log_file, "TIME,%d,EVENT,Init finished\n", tick);
    f_sync(&log_file);
}

void logHandle(void) {
    f_lseek(&log_file, f_size(&log_file));
    f_printf(&log_file, "TIME,%d,roll:,%d,cx:,%d,cy:,%d\n",
             tick,
             int32_t(flight_control.missile_earth_frame_.euler_angle.roll * 1000),
             uint8_t(circle.cx),
             uint8_t(circle.cy));

    static uint16_t auto_save_tick = 0;
    if (auto_save_tick >= 100) {
        f_sync(&log_file);
        auto_save_tick = 0;
    }
    auto_save_tick++;

    if (log_stop) {
        logStop();
    }
}

void logStop(void) {
    f_printf(&log_file, "TIME,%d,EVENT,Log stopped manually\n", tick);
    f_close(&log_file);
}

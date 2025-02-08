/**
******************************************************************************
* @file : mt9v034_driver.h
* @author : Albert Wang
* @brief : https://zhuanlan.zhihu.com/p/673556009
* @date : 2023/12/21
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef GUIDEDMISSILE_MT9V034_DRIVER_H
#define GUIDEDMISSILE_MT9V034_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#include "string.h"
#include "missile_config.h"

#define DEVICE_ADDR 0xB8

#define CHIP_ID_ADDR 0x00
#define CHIP_ID_VALUE 0x1324

#define ROW_START_ADDR 0x01
#define ROW_START_VALUE 0x01

#define COL_START_ADDR 0x02
#define COL_START_VALUE 0x04

#define WINDOWS_HEIGHT_ADDR 0x03
#define WINDOWS_HEIGHT_VALUE 480

#define WINDOW_WIDTH_ADDR 0x04
#define WINDOW_WIDTH_VALUE 752

#define HORIZONTAL_BLANKING_ADDR 0x05
#define HORIZONTAL_BLANKING_VALUE 91

#define CHIP_CONTROL_ADDR 0x07
#define CHIP_CONTROL_VALUE 0x188

#define COARSE_SHUTTER_WIDTH_1_ADDR 0x08
#define COARSE_SHUTTER_WIDTH_1_VALUE 0x1BB
#define COARSE_SHUTTER_WIDTH_2_ADDR 0x09
#define COARSE_SHUTTER_WIDTH_2_VALUE 0x1D9
#define COARSE_SHUTTER_WIDTH_3_ADDR 0x0A
#define COARSE_SHUTTER_WIDTH_3_VALUE 0x164
#define COARSE_SHUTTER_WIDTH_TOTAL_ADDR 0x0B
#define COARSE_SHUTTER_WIDTH_TOTAL_VALUE 100 // Related to exposure time

#define RESET_ADDR 0x0C
#define RESET_VALUE 0x01

#define VERTICAL_BLANKING_ADDR 0x06
// Value = COARSE_SHUTTER_WIDTH_TOTAL_VALUE-COARSE_SHUTTER_WIDTH_1_ADDR+7

#define READ_MODE_ADDR 0x0D
#define READ_MODE_VALUE 0x0A // 4*4 binning mode & flip row and column

#define SENSOR_TYPE_CONTROL_ADDR 0x0F
#define SENSOR_TYPE_CONTROL_VALUE 0x00 // Linear opeartion & mono sensor

#define ADC_COMPANDING_MODE_ADDR 0x1C
#define ADC_COMPANDING_MODE_VALUE 0x202

#define ROW_NOISE_CORRECTION_CONTROL_ADDR 0x70
#define ROW_NOISE_CORRECTION_CONTROL_VALUE 0x00

#define TILED_DIGITAL_GAIN_ADDR 0x80
#define TILED_DIGITAL_GAIN_VALUE 0xAFA

#define AEC_AGC_DESIRED_BIN_ADDR 0xA5
#define AEC_AGC_DESIRED_BIN_VALUE 0x3A

#define AEC_LOW_PASS_FILTER_ADDR 0xA8
#define AEC_LOW_PASS_FILTER_VALUE 0x01

#define AGC_LOW_PASS_FILTER_ADDR 0xAA
#define AGC_LOW_PASS_FILTER_VALUE 0x02

#define AGC_AEC_BIN_DIFFERENCE_THRESHOLD_ADDR 0xAE
#define AGC_AEC_BIN_DIFFERENCE_THRESHOLD_VALUE 0x0A

#define AGC_AEC_ENABLE_ADDR 0xAF
#define AGC_AEC_ENABLE_VALUE 0x02 // Enable AGC & disable AEC

void mt9Init(void);

void mt9RegWrite(uint16_t addr, uint16_t data);

void mt9RegRead(uint16_t addr, uint16_t *pData);

extern uint16_t i2c_read_value;

#ifdef __cplusplus
}
#endif

#endif //GUIDEDMISSILE_MT9V034_DRIVER_H

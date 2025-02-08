/**
******************************************************************************
* @file : mt9v034_driver.c
* @author : Albert Wang
* @brief : https://zhuanlan.zhihu.com/p/673556009
* @date : 2023/12/21
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "mt9v034_driver.h"

uint16_t i2c_read_value;

void mt9Init(void) {
    mt9RegRead(CHIP_ID_ADDR, &i2c_read_value); //TODO: 判断读取是否正确，写入日志
    if (i2c_read_value == CHIP_ID_VALUE) {

    }

    // Write reserved registers per Rev G datasheet table 8 recommendations
    mt9RegWrite(0x13, 0x2D2E);
    mt9RegWrite(0x20, 0x03C7);
    mt9RegWrite(0x24, 0x001B);
    mt9RegWrite(0x2B, 0x0003);
    mt9RegWrite(0x2F, 0x0003);

    mt9RegWrite(ROW_START_ADDR, ROW_START_VALUE);
    mt9RegWrite(COL_START_ADDR, COL_START_VALUE);
    mt9RegWrite(WINDOWS_HEIGHT_ADDR, WINDOWS_HEIGHT_VALUE);
    mt9RegWrite(WINDOW_WIDTH_ADDR, WINDOW_WIDTH_VALUE);
    mt9RegWrite(HORIZONTAL_BLANKING_ADDR, HORIZONTAL_BLANKING_VALUE);
    mt9RegWrite(VERTICAL_BLANKING_ADDR, COARSE_SHUTTER_WIDTH_TOTAL_VALUE - COARSE_SHUTTER_WIDTH_1_ADDR + 7);
    mt9RegWrite(CHIP_CONTROL_ADDR, CHIP_CONTROL_VALUE);
    mt9RegWrite(COARSE_SHUTTER_WIDTH_1_ADDR, COARSE_SHUTTER_WIDTH_1_VALUE);
    mt9RegWrite(COARSE_SHUTTER_WIDTH_2_ADDR, COARSE_SHUTTER_WIDTH_2_VALUE);
    mt9RegWrite(COARSE_SHUTTER_WIDTH_3_ADDR, COARSE_SHUTTER_WIDTH_3_VALUE);
    mt9RegWrite(COARSE_SHUTTER_WIDTH_TOTAL_ADDR, COARSE_SHUTTER_WIDTH_TOTAL_VALUE);
    mt9RegWrite(SENSOR_TYPE_CONTROL_ADDR, SENSOR_TYPE_CONTROL_VALUE);
    mt9RegWrite(READ_MODE_ADDR, READ_MODE_VALUE);
    mt9RegWrite(ADC_COMPANDING_MODE_ADDR, ADC_COMPANDING_MODE_VALUE);
    mt9RegWrite(ROW_NOISE_CORRECTION_CONTROL_ADDR, ROW_NOISE_CORRECTION_CONTROL_VALUE);
    mt9RegWrite(AEC_AGC_DESIRED_BIN_ADDR, AEC_AGC_DESIRED_BIN_VALUE);
    mt9RegWrite(AEC_LOW_PASS_FILTER_ADDR, AEC_LOW_PASS_FILTER_VALUE);
    mt9RegWrite(AGC_LOW_PASS_FILTER_ADDR, AGC_LOW_PASS_FILTER_VALUE);
    mt9RegWrite(AGC_AEC_BIN_DIFFERENCE_THRESHOLD_ADDR, AGC_AEC_BIN_DIFFERENCE_THRESHOLD_VALUE);
    mt9RegWrite(AGC_AEC_ENABLE_ADDR, AGC_AEC_ENABLE_VALUE);

    for (uint8_t i = 0; i <= 23; i++) {
        mt9RegWrite(TILED_DIGITAL_GAIN_ADDR + i, TILED_DIGITAL_GAIN_VALUE);
    }

    mt9RegWrite(RESET_ADDR, RESET_VALUE);
}

void mt9RegWrite(uint16_t addr, uint16_t data) {
    uint16_t data_buf;
    data_buf = data;
    uint8_t write_buf[2] = {data_buf >> 8, data_buf};
    HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDR, addr, I2C_MEMADD_SIZE_8BIT, write_buf, 2, 100);
}

void mt9RegRead(uint16_t addr, uint16_t *pData) {
    uint8_t i2c_read_buf[2];
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, addr, I2C_MEMADD_SIZE_8BIT, i2c_read_buf, 2, 100);
    *pData = (uint16_t) ((i2c_read_buf[0] << 8) | i2c_read_buf[1]);
}

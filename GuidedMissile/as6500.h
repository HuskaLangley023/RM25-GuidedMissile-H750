//
// Created by zhu_y on 2025/2/8.
//

#ifndef AS6500_H
#define AS6500_H

#ifdef __cplusplus
extern "C"{
#endif

#include "main.h"

//两个磁编码器地址0x36，通过I2C1和I2C2通讯
#define AS6500_ADDR 0x36

class Encoder {
public:
    I2C_HandleTypeDef* hi2c_;
    uint16_t angle_beg_;//用于初始化
    uint16_t raw_angle_;//angle与raw_angle为限幅下的缩放关系，此处不限幅，范围360deg，故二者一一对应
    float current_angle_;//raw_angle_16转10

    Encoder(I2C_HandleTypeDef*);
    void asinit();
    uint8_t asRegReadBit(uint16_t);
    void asRegWriteBit(uint8_t, uint16_t);
    void asHandle();
    float raw2deg(uint16_t);
};

void as6500init();

#ifdef __cplusplus
}
#endif

#endif //AS6500_H

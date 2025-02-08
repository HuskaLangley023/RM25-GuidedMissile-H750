//
// Created by zhu_y on 2025/2/8.
//
#include "as6500.h"
#include "i2c.h"


#ifdef ENCODER_LR
Encoder encoder_l(&hi2c1);
Encoder encoder_r(&hi2c2);
#endif
#ifdef ENCODER_UP
Encoder encoder_l(&hi2c?); //TODO H750仅两条I2C总线，三个编码器地址相同，分配问题待解决
#endif


Encoder::Encoder(I2C_HandleTypeDef *hi2c): hi2c_(hi2c) {
}

uint8_t test; //测试是否正常读取 0x0B STATUS
void Encoder::asinit() {
    uint8_t h, l;
    h = asRegReadBit(0x0C);
    l = asRegReadBit(0x0D);
    asRegWriteBit(h, 0x01);
    asRegWriteBit(l, 0x02);
    HAL_Delay(5);

    test = asRegReadBit(0x0B); //test
} //TODO 调式判断初始化正确性 ？是否要读取rawangle，或是直接写入0与4096

uint8_t Encoder::asRegReadBit(uint16_t addr) {
    uint8_t tag = AS6500_ADDR << 1 | 0X00; //R
    uint8_t i2c_read_buf;
    HAL_I2C_Mem_Read(hi2c_, tag, addr,I2C_MEMADD_SIZE_8BIT, &i2c_read_buf, 1, 100);
    return i2c_read_buf;
}

void Encoder::asRegWriteBit(uint8_t meg, uint16_t addr) {
    uint8_t tag = AS6500_ADDR << 1 | 0X01; //W
    HAL_I2C_Mem_Write_IT(hi2c_, tag, addr,I2C_MEMADD_SIZE_8BIT, &meg, 1);
}

void Encoder::asHandle() {
    uint8_t h, l;
    h = asRegReadBit(0x0C);
    l = asRegReadBit(0x0D);
    raw_angle_ = h << 8 | l;
    current_angle_ = raw2deg(raw_angle_);
}

float Encoder::raw2deg(uint16_t in) {
    float out = (float) in * 360.f / 4096;
    return out;
}


void as6500init() {
#ifdef ENCODER_LR
    encoder_l.asinit();
    encoder_r.asinit();
#endif
#ifdef ENCODER_UP
    encoder_l.asinit();
#endif
}



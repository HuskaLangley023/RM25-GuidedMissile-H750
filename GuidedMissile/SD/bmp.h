/**
******************************************************************************
* @file : bmp.h
* @author : Albert Wang
* @brief : None
* @date : 2024/1/16
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_BMP_H
#define RM24_GUIDEDMISSILE_H750_BMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "missile_config.h"
#include "string.h"

//BMP头文件
typedef struct {
    uint16_t bfType;     //文件标志.只对'BM',用来识别BMP位图类型
    uint32_t bfSize;      //文件大小,占四个字节
    uint16_t bfReserved1;//保留
    uint16_t bfReserved2;//保留
    uint32_t bfOffBits;  //从文件开始到位图数据(bitmap data)开始之间的的偏移量
} __attribute__((__packed__)) BITMAPFILEHEADER;
//BMP信息头
typedef struct {
    uint32_t biSize;                //说明BITMAPINFOHEADER结构所需要的字数。
    int32_t biWidth;            //说明图象的宽度，以象素为单位
    int32_t biHeight;        //说明图象的高度，以象素为单位
    uint16_t biPlanes;            //为目标设备说明位面数，其值将总是被设为1
    uint16_t biBitCount;        //说明比特数/象素，其值为1、4、8、16、24、或32
/*说明图象数据压缩的类型。其值可以是下述值之一：
BI_RGB：没有压缩；
BI_RLE8：每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；  
BI_RLE4：每个象素4比特的RLE压缩编码，压缩格式由2字节组成
BI_BITFIELDS：每个象素的比特由指定的掩码决定。*/
    uint32_t biCompression;
    uint32_t biSizeImage;        //说明图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0
    int32_t biXPelsPerMeter;    //说明水平分辨率，用象素/米表示
    int32_t biYPelsPerMeter;    //说明垂直分辨率，用象素/米表示
    uint32_t biClrUsed;            //说明位图实际使用的彩色表中的颜色索引数
    uint32_t biClrImportant;    //说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
} __attribute__((__packed__)) BITMAPINFOHEADER;
//彩色表 
typedef struct {
    uint8_t rgbBlue;    //指定蓝色强度
    uint8_t rgbGreen;    //指定绿色强度
    uint8_t rgbRed;        //指定红色强度
    uint8_t rgbReserved;//保留，设置为0
} __attribute__((__packed__)) RGBQUAD;
//整体信息头
typedef struct {
    BITMAPFILEHEADER bmfHeader;
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD RGB_MASK[256];            //调色板用于存放RGB掩码.
} __attribute__((__packed__)) BITMAPINFO;

void bmpInit(void);

void bmpCache(void);

void bmpSave(void);

extern uint8_t image_cache[10][HEIGHT / 2][96];

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_BMP_H

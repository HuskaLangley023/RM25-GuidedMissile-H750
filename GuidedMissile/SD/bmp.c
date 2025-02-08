/**
******************************************************************************
* @file : bmp.c
* @author : Albert Wang
* @brief : None
* @date : 2024/1/16
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "bmp.h"
#include "sd.h"
#include "fatfs.h"

uint8_t image_cache[10][HEIGHT / 2][96];

BITMAPINFO bmp;
FIL pic_file;
uint32_t fnum;

void bmpInit(void) {
    //填写文件信息头信息
    bmp.bmfHeader.bfType = 0x4D42;            //bmp类型  "BM"
    bmp.bmfHeader.bfSize = 54 + (256 * 4) + (HEIGHT / 2) * (96);    //文件大小（信息结构体+像素数据）
    bmp.bmfHeader.bfReserved1 = 0x0000;        //保留，必须为0
    bmp.bmfHeader.bfReserved2 = 0x0000;
    bmp.bmfHeader.bfOffBits = 54 + (256 * 4);                //位图信息结构体所占的字节数

    //填写位图信息头信息
    bmp.bmiHeader.biSize = 40;            //位图信息头的大小
    bmp.bmiHeader.biWidth = 96;        //位图的宽度
    bmp.bmiHeader.biHeight = -HEIGHT / 2;        //图像的高度
    bmp.bmiHeader.biPlanes = 1;            //目标设别的级别，必须是1
    bmp.bmiHeader.biBitCount = 8;        //每像素位数
    bmp.bmiHeader.biCompression = 0;    //压缩
    bmp.bmiHeader.biSizeImage = 0;//实际位图所占用的字节数（仅考虑位图像素数据）
    bmp.bmiHeader.biXPelsPerMeter = 0;    //水平分辨率
    bmp.bmiHeader.biYPelsPerMeter = 0;    //垂直分辨率
    bmp.bmiHeader.biClrImportant = 256;    //说明图像显示有重要影响的颜色索引数目，0代表所有的颜色一样重要
    bmp.bmiHeader.biClrUsed = 256;        //位图实际使用的彩色表中的颜色索引数，0表示使用所有的调色板项

    for (uint16_t p = 0; p < 256; p++) {
        bmp.RGB_MASK[p].rgbBlue = (uint8_t) p;
        bmp.RGB_MASK[p].rgbGreen = (uint8_t) p;
        bmp.RGB_MASK[p].rgbRed = (uint8_t) p;
        bmp.RGB_MASK[p].rgbReserved = (uint8_t) 0;
    }
}

void bmpCache() {
    static uint8_t count;
    if (count < 10) {
        memcpy(&image_cache[count], &image_compressed, sizeof(image_compressed));
        count++;
    }
}

void bmpSave() {
    char file_path[16];
    for (uint8_t i = 0; i <= 9; i++) {
        sprintf(file_path, "0:/%d/%d.bmp", dir_num, i);

        f_open(&pic_file, file_path, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
        f_write(&pic_file, &bmp, sizeof(bmp), &fnum);
        f_lseek(&pic_file, bmp.bmfHeader.bfOffBits);
        f_write(&pic_file, image_cache[i], sizeof(image_cache[i]), &fnum);
        f_close(&pic_file);
    }
}

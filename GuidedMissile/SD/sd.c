/**
******************************************************************************
* @file : sd.c
* @author : Albert Wang
* @brief : None
* @date : 2024/4/16
******************************************************************************
* Copyright (c) 2024 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "sd.h"
#include "fatfs.h"

uint8_t dir_num = 0;

void sdInit() {
    FRESULT res;
    DIR dir;
    FILINFO fno;
    char *path = "0:/";

    f_mount(&SDFatFS, path, 1);
    res = f_opendir(&dir, path); /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno); /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) {
                break;  /* Break on error or end of dir */
            }
            if (fno.fattrib & AM_DIR) { /* It is a directory */
                dir_num++;
            }
        }
        sprintf(path, "0:/%d", dir_num);
        f_mkdir(path);
    }
}

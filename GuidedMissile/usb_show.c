/**
******************************************************************************
* @file : usb_show.c
* @author : Albert Wang
* @brief : None
* @date : 2023/12/24
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#include "usb_show.h"
#include "usbd_cdc_if.h"
#include "light_recognition.h"

uint8_t tx_data[HEIGHT / 2 + 1][96];
uint8_t usb_stop;

void usbHandle(void) {
    tx_data[0][0] = 204;
    tx_data[0][1] = 208;
    tx_data[0][2] = 216;
    tx_data[0][3] = usb_stop;
    tx_data[0][4] = circle.cx;
    tx_data[0][5] = circle.cy;
    tx_data[0][6] = circle.radius; // radius = 0 means no circle found
    tx_data[0][7] = cv_fps;
    memcpy(&tx_data[0] + 1, image_compressed, sizeof(image_compressed));
    CDC_Transmit_FS((uint8_t *) tx_data, sizeof(tx_data));
}

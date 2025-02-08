/**
******************************************************************************
* @file : usb_show.h
* @author : Albert Wang
* @brief : None
* @date : 2023/12/24
******************************************************************************
* Copyright (c) 2023 Team JiaoLong-SJTU
* All rights reserved.
******************************************************************************
*/

#ifndef RM24_GUIDEDMISSILE_H750_USB_SHOW_H
#define RM24_GUIDEDMISSILE_H750_USB_SHOW_H

#ifdef __cplusplus
extern "C" {
#endif

#include "missile_config.h"
#include "stdint.h"

void usbHandle(void);

extern uint8_t tx_data[HEIGHT / 2 + 1][96];
extern uint8_t usb_stop;

#ifdef __cplusplus
}
#endif

#endif //RM24_GUIDEDMISSILE_H750_USB_SHOW_H

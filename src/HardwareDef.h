//===========================================================================================================
//   The information contained herein is the exclusive property of Analog & Digital Microelectronics Limited.
// 
//   And shall not be distributed, reproduced,or disclosed in whole in part without prior written permission.
// 
//       (C) COPYRIGHT 2012   Analog & Digital Microelectronics Limited.                            
// 
//                   ALL RIGHTS RESERVED
// 
//   The entire notice above must be reproduced on all authorized copies.
//===========================================================================================================
// Project: PS 1008 DEMO CODE
// Original Author: FAE - Kenny Yeh
// Ver: V1.0.0   2024-10-10  Kenny Yeh   1.first version
// 
// 
//===========================================================================================================
#ifndef __HARDWARE_DEF_H__
#define __HARDWARE_DEF_H__
#include "PS1008.h"
#define PA_UNUSE_BIT    0x00
#define PB_UNUSE_BIT    0x00
#define PIN_CLK   PB2
#define BIT_CLK   2
#define TRI_CLK   TRISB2

#define PIN_DAT   PB1
#define BIT_DAT   1
#define TRI_DAT   TRISB1

#define PIN_PDRV   PB6
#define BIT_PDRV   6
#define TRI_PDRV   TRISB6

//------input pin ------

#define PIN_KEY   PB0
#define BIT_KEY   0
#define TRI_KEY   TRISB0

#define PIN_OUT   PB7
#define BIT_OUT   7
#define TRI_OUT   TRISB7

#define WAKEUP_PB_PIN   (1 << BIT_KEY)  | (1 << BIT_CLK) | (1 << BIT_DAT)

//------out put pin ------
#define RGB_PA    0x00
#define RGB_PB    0x10

#define SEGTUBE_PA    0x1F	//PA0~PA4
#define SEGTUBE_PB    0x20	//PB5

// #define PIN_FANTIS_EN   PB6
// #define BIT_FANTIS_EN   6
// #define TRI_FANTIS_EN   TRISB6

// #define PIN_FANTIS_DAT   PINB5
// #define BIT_FANTIS_DAT   5
// #define TRI_FANTIS_DAT   TRISB5

#endif
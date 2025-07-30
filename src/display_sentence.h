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
#ifndef __DISPLAY_SENTENCE_H__
#define __DISPLAY_SENTENCE_H__

#include "PS1008.h"
#include "common.h"
#include <stdio.h>
#include "segtube.h"
#include "rgb_led.h"

// ===========RGB MODE定义===========
#define SEGTUBE_LED          0X07       //数码管模式
#define SEGTUBE_SET           0x08        //(油量外框，闪电，百分号)
#define SEGTUBE_SCREENOFF     0x0A       //灭全屏模式
// #define NIXTETUBE_FULLSCREEN    0x0B       //显全屏模式
#define FLASHICON_SET           0x0C        //(油量外框，闪电，百分号)
#define LOOP_START              0x10
#define LOOP_END                0x11
#define DISPLAY_END             0x80       //灯效停止

#define NUM_OFF         0xFF
// #define NUM_ALL         0xEE
#define NUM_BY_REG      0xFE        //电量由R_Battery_Percent决定;
#define OIL_BY_REG      0xFE        //油量由R_OilLevel决定；
// #define NUM_BY_STEP     0XC

#define ICON_FLA     0x01
#define ICON_PER     0x02
#define ICON_CY1     0x04
#define ICON_CY2     0x08
#define ICON_CY3     0x10
#define ICON_CY4     0x20
#define ICON_CY5     0x40
#define ICON_CYCLE   0x7C
#define ICON_ALL      0x7f

#define M_SHOW_NUM_LED(icon,oil,num,color,ontime,offtime,cycle,time)  SEGTUBE_LED,(time>>11),((time>>3)&0x0FF),icon,oil,num,color,(ontime/8),(offtime/8),cycle
#define M_SHOW_NUM(icon,oil,num,time)           SEGTUBE_SET,(time>>11),((time>>3)&0x0FF),icon,oil,num     //flag bit0:bit1;bit2 = H1_flash:H2_percent:K5~K9_oil_cycle; 
#define M_SEGTUBE_SCREENOFF(time)     SEGTUBE_SCREENOFF,(time>>11),((time>>3)&0x0FF)
// #define M_NIXTETUBE_FULLSCREEN(time)    NIXTETUBE_FULLSCREEN,(time>>11),((time>>3)&0x0FF)
#define M_FLASHSET(icon,time)           FLASHICON_SET,(time>>11),((time>>3)&0x0FF),icon     //flag bit0:bit1;bit2 = H1_flash:H2_percent:K5~K9_oil_cycle; 
#define M_LOOP_START(times)             LOOP_START,times             
#define M_LOOP_END                      LOOP_END 
extern u8 R_Light_Idx;
extern u8 R_Light_Cnt;
extern bit b_LightPlay_Flag;
extern u16 R_Light_Time_Cnt;
extern u8 R_Light_LoopTimes;
extern u8 R_Light_LoopCnt_ADDR;

void F_PlayLight(u8 LightIdx);
void F_PlayLight_8ms(void);
void F_StopLight(void);
#endif

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
#ifndef _COMMON_H_
#define _COMMON_H_

#include "PS1008.h"
#include <stdio.h>
#include "commdef.h"
#include "smoke.h"
#include "setting.h"


//下面两个宏联合起来,实现把A与B的宏值连在一起, 适用于从io的位号向IO位变量的转换
#define __CONNECT(A,bit) A##bit
#define _CONNECT(A,bit) __CONNECT(A, bit)

#define D_8ms_200ms     200/8
#define D_8ms_600ms     600/8
#define D_8ms_1S        1000/8
#define D_8ms_2S        2000/8
#define D_8ms_5S        5000/8
#define D_8ms_20S       20000/8

/************************GLOBAL VARIABLES********************/
extern u8  R_T1_cnt;
extern u8 R_Battery_Percent;//转成百分比的电池电量值,最大100, 最小0
extern u16 R_EngCnt;        //口数对应电量
/*油量相关变量*/
extern u16 R_OilRest;//吸烟油量计数 颗粒度1s
extern u8 R_OilCnt; //抽烟秒数

#ifdef _RV_DET_SMKING_
extern bit b_CheckRing_Flag;
#endif
extern bit b_PowerOn_Flag;
extern bit b_T1_Flag;
extern bit b_T8ms_Flag;

extern u16 R_Sleep_Off;//灯效显示结束后等待睡眠时间
extern u8  ChargeJudeCnt;//充电插入中断到充电移除中断时间计数
extern u16 R_ADC_VBAT;//采集VBAT 的ADC 值
extern u32 R_Temp32;
extern u16 R_Temp16_0;
extern u16 R_Temp16_1;
extern u8 R_Temp0;
extern u8 R_Temp1;



unsigned int F_ADC2VBAT(unsigned int voltage);
void F_System_Init(void);
void init_variables(void);
void Timer0_Init(void);
void Timer1_Init(void);
void F_VADC_Sample_VOUT(void);
void F_VADC_Sample_VBAT(void);
void F_Start_SampBAT(void); 
void F_Start_SampVIN(void);
unsigned int F_VADC_Sample(void);
void F_Work_PowerOff(void);



#endif

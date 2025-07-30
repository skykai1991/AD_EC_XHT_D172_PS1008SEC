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
#ifndef __CHARGE__
#define __CHARGE__

#include "commdef.h"

extern bit b_ChargeFlag;
extern bit b_UsbInFlag; 
// extern bit b_ChargeFullFlag;
// extern u8 R_SampBATTimes;
// extern u16 R_DAC_BAT_Result;
// extern u8 R_ChargeFullDebounce;
void F_Start_SampBAT(void);
void F_WorkCharge(void);
void F_CalculateEneryPercent(void);

#endif
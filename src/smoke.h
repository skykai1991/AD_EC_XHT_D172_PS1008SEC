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
#ifndef __SMOKE_H__
#define __SMOKE_H__

#include "PS1008.h"
#include "common.h"
#include <stdio.h>
typedef union ByteType_ErrFlag{		//共用体变量类型（8bit）
    struct {
		unsigned char ErrFlag;
    };

    struct {
		unsigned	HZ		: 1;	//高阻
		unsigned	LZ		: 1;	//低阻
		unsigned	OT		: 1;	//超时
		unsigned	LB		: 1;	//低电
		unsigned	OPEN	: 1;	//开路
    };
};

#ifdef _BOMB_INOUT_DETECT_
extern bit b_Bomb_Online;		// 1: have bomb  0: no bomb
#endif

extern bit b_SmokeFlag;			// 1:smoking     0:not smoke
// extern bit b_HLR_Flag;
extern union ByteType_ErrFlag  R_ErrFlag;
void F_SMK_Init(void);
void F_AFE_Event(void);
void F_WorkSmoke(void);
void F_SmokingRV_Det(void);


#endif

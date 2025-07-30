#ifndef __MIC_H__
#define __MIC_H__

#include "PS1008.h"
#include "commdef.h"
#include "PS1008_DEF.h"

#define M_SMKORIG {b_InputRecord_Last = b_InputCurrent = 0;}
// void F_KeyInit(void);
void F_MICInput(void);

extern bit b_InputCurrent;   //单次扫描当前状态
extern bit b_InputLast;      //单次扫描上次状态
extern bit b_InputRecord;    //消抖后，按键的状态记录
extern bit b_InputRecord_Last;   //消抖后，上一次按键的状态记录
extern bit b_InputPress;     //有效的按键按下
extern bit b_InputRelease;   //有效的按键松开
// extern u8 R_KeyDelayCnt;
// extern u8 R_KeyHit_Cnt;
extern u8 R_DebounceCnt; //消抖计数
#endif
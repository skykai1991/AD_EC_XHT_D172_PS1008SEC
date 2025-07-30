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
#ifndef __NIXIE_TUBE_H__
#define __NIXIE_TUBE_H__
#include "PS1008.h" 
#include "common.h"
#include <stdio.h>
#include "HardwareDef.h"
// ===========I/O属性寄存器配置=====================
#define SEGTUBE_P1   PA4     //1
#define SEGTUBE_P2   PA3     //2
#define SEGTUBE_P3   PA2     //3
#define SEGTUBE_P4   PA1     //4
#define SEGTUBE_P5   PA0     //5
#define SEGTUBE_P6   PB5     //6
#define TRIS_SEGTUBE_P1    TRISA4      //1
#define TRIS_SEGTUBE_P2    TRISA3      //2
#define TRIS_SEGTUBE_P3    TRISA2      //3
#define TRIS_SEGTUBE_P4    TRISA1      //4
#define TRIS_SEGTUBE_P5    TRISA0      //5
#define TRIS_SEGTUBE_P6    TRISB5      //6
#define TRIS_INPUT        1
#define TRIS_OUTPUT       0
//共阴极扫描，通过tris寄存器（IO方向）控制，tris寄存器0表示输出，1表示输入
//R_Lcd_Bufx通过bit位 1/0 表示灯 亮/灭
#define ctrl(x)		(~x)	

//阴极IO控制（低电平灯亮）
#define	TRIS_SEGTUBE_P1_ON()		TRIS_SEGTUBE_P1 = 0; SEGTUBE_P1 = 0
#define	TRIS_SEGTUBE_P1_OFF()		TRIS_SEGTUBE_P1 = 1; SEGTUBE_P1 = 1
#define	TRIS_SEGTUBE_P2_ON()		TRIS_SEGTUBE_P2 = 0; SEGTUBE_P2 = 0
#define	TRIS_SEGTUBE_P2_OFF()		TRIS_SEGTUBE_P2 = 1; SEGTUBE_P2 = 1
#define	TRIS_SEGTUBE_P3_ON()		TRIS_SEGTUBE_P3 = 0; SEGTUBE_P3 = 0
#define	TRIS_SEGTUBE_P3_OFF()		TRIS_SEGTUBE_P3 = 1; SEGTUBE_P3 = 1
#define	TRIS_SEGTUBE_P4_ON()		TRIS_SEGTUBE_P4 = 0; SEGTUBE_P4 = 0
#define	TRIS_SEGTUBE_P4_OFF()		TRIS_SEGTUBE_P4 = 1; SEGTUBE_P4 = 1
#define	TRIS_SEGTUBE_P5_ON()		TRIS_SEGTUBE_P5 = 0; SEGTUBE_P5 = 0
#define	TRIS_SEGTUBE_P5_OFF()		TRIS_SEGTUBE_P5 = 1; SEGTUBE_P5 = 1
#define	TRIS_SEGTUBE_P6_ON()		TRIS_SEGTUBE_P6 = 0; SEGTUBE_P6 = 0
#define	TRIS_SEGTUBE_P6_OFF()		TRIS_SEGTUBE_P6 = 1; SEGTUBE_P6 = 1
// ===========LED屏与LED RAM映射定义===========
// ===========   LED RAM   ===================
//               bit0  bit1  bit2  bit3  bit4  bit5  bit6  bit7 
// R_Lcd_Buf0:   FLA   PER   CY1   CY2   CY3   CY4   CY5    	//OIL CYCLE CY1-5  
// R_Lcd_Buf1:   A1    B1    C1    D1    E1    F1    G1    J3
// R_Lcd_Buf2:   A2    B2    C2    D2    E2    F2    G2    *
// R_Lcd_Buf3:   K1    K2    K3    K4                 *	//OIL LEVEL 1-4
typedef union ByteType_DisplayBuffer{		//共用体变量类型（8bit）
    struct {
		unsigned char buf;
    };

    struct {
		unsigned	A		: 1;	//bit0
		unsigned	B		: 1;
		unsigned	C		: 1;
		unsigned	D		: 1;
		unsigned	E		: 1;
		unsigned	F		: 1;
		unsigned	G		: 1;
		unsigned	H		: 1;
    };
    struct {
		unsigned	FLA		: 1;	//bit0
		unsigned	PER		: 1;
		unsigned	CY1		: 1;
		unsigned	CY2		: 1;
		unsigned	CY3		: 1;
		unsigned	CY4		: 1;
		unsigned	CY5		: 1;
    };
    struct {
		unsigned	K1		: 1;	//bit0
		unsigned	K2		: 1;
		unsigned	K3		: 1;
		unsigned	K4		: 1;
    };
};
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf0;
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf1;
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf2;
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf3;


// ===========LED屏layout映射定义===========
// ===========OLED LAYOUT======================================
//         positive->     pin1    pin2    pin3    pin4    pin5    pin6
// negative     pin1       *       A2      C2      E2      K1      CY3 
//              pin2       B2      *       A1      PER     K2      CY4
//              pin3       D2      B1      *       FLA     K3      CY5
//              pin4       F2      D1      C1      *       K4      CY1
//              pin5       G2      E1      F1      G1      *       CY2
// ===========================================================
#define	F_SegTubeScan_P12		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf2.A)
#define	F_SegTubeScan_P13		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf2.C)
#define	F_SegTubeScan_P14		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf2.E)
#define	F_SegTubeScan_P15		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf3.K1)
#define	F_SegTubeScan_P16		TRIS_SEGTUBE_P6 = ctrl(R_Lcd_Buf0.CY3)

#define	F_SegTubeScan_P21		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.B)
#define	F_SegTubeScan_P23		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.A)
#define	F_SegTubeScan_P24		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf0.PER)
#define	F_SegTubeScan_P25		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf3.K2)
#define	F_SegTubeScan_P26		TRIS_SEGTUBE_P6 = ctrl(R_Lcd_Buf0.CY4)

#define	F_SegTubeScan_P31		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.D)
#define	F_SegTubeScan_P32		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.B)
#define	F_SegTubeScan_P34		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf0.FLA)
#define	F_SegTubeScan_P35		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf3.K3)
#define	F_SegTubeScan_P36		TRIS_SEGTUBE_P6 = ctrl(R_Lcd_Buf0.CY5)

#define	F_SegTubeScan_P41		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.F)
#define	F_SegTubeScan_P42		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.D)
#define	F_SegTubeScan_P43		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.C)
#define	F_SegTubeScan_P45		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf3.K4)
#define	F_SegTubeScan_P46		TRIS_SEGTUBE_P6 = ctrl(R_Lcd_Buf0.CY1)

#define	F_SegTubeScan_P51		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.G)
#define	F_SegTubeScan_P52		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.E)
#define	F_SegTubeScan_P53		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.F)
#define	F_SegTubeScan_P54		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf1.G)
#define	F_SegTubeScan_P56		TRIS_SEGTUBE_P6 = ctrl(R_Lcd_Buf0.CY2)

extern bit b_SegTubeEn;
extern bit b_SegTubeScanReq;
void F_SegTubeScan(void);
extern const unsigned char numtab[];
//==============================================================
// name:F_ShowSegTube
// input:IconFlag-- Bit0: E icon   Bit1: percent icon bit 2~6: oil cycle icon
//       OilLevel--- oil level: 0~4 level0~level4
//       num ---- num 0~99
//==============================================================
void F_ShowSegTube(u8 IconFlag, u8 OilLevel,u8 num);
// ===========show function Macro define==============================
#define M_Show_Tenbit(num) R_Lcd_Buf1.buf = numtab[num];
#define M_Show_Unitbit(num) R_Lcd_Buf2.buf = numtab[num];
#define M_ClrFlag R_Lcd_Buf0.buf = 0;
#define M_ClrOil R_Lcd_Buf3.buf = 0;

#define M_ClearPanel R_Lcd_Buf0.buf = R_Lcd_Buf1.buf = R_Lcd_Buf2.buf = R_Lcd_Buf3.buf = 0x00;
#define M_FufillPanel R_Lcd_Buf0.buf = R_Lcd_Buf1.buf = R_Lcd_Buf2.buf = R_Lcd_Buf3.buf = 0xff;
#define M_SegTube_Init    {TRISA |= SEGTUBE_PA; PORTA |= SEGTUBE_PA;TRISB |= SEGTUBE_PB; PORTB |= SEGTUBE_PB;}                 
// ===================================================================


#endif
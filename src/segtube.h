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
#define SEGTUBE_P2   PA2     //2
#define SEGTUBE_P3   PA1     //3
#define SEGTUBE_P4   PA0     //4
#define SEGTUBE_P5   PB5     //5
// #define SEGTUBE_P6   PB5     //6
#define TRIS_SEGTUBE_P1    TRISA4      //1
#define TRIS_SEGTUBE_P2    TRISA2      //2
#define TRIS_SEGTUBE_P3    TRISA1      //3
#define TRIS_SEGTUBE_P4    TRISA0      //4
#define TRIS_SEGTUBE_P5    TRISB5      //5
// #define TRIS_SEGTUBE_P6    TRISB5      //6
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
// #define	TRIS_SEGTUBE_P6_ON()		TRIS_SEGTUBE_P6 = 0; SEGTUBE_P6 = 0
// #define	TRIS_SEGTUBE_P6_OFF()		TRIS_SEGTUBE_P6 = 1; SEGTUBE_P6 = 1
// ===========LED屏与LED RAM映射定义===========
// ===========   LED RAM   ===================
//               bit0  bit1  bit2  bit3  bit4  bit5  bit6  bit7 
// R_Lcd_Buf0:   B1    C1    K1    K2    K3    K4    *      *   	
// R_Lcd_Buf1:   A2    B2    C2    D2    E2    F2    G2     *
// R_Lcd_Buf2:   A3    B3    C3    D3    E3    F3    G3     *

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
    // struct {
	// 	unsigned	FLA		: 1;	//bit0
	// 	unsigned	PER		: 1;
	// 	unsigned	CY1		: 1;
	// 	unsigned	CY2		: 1;
	// 	unsigned	CY3		: 1;
	// 	unsigned	CY4		: 1;
	// 	unsigned	CY5		: 1;
    // };
    struct {
		unsigned    B1       : 1;	//bit0
		unsigned    C1       : 1;
		unsigned	K1		: 1;	
		unsigned	K2		: 1;
		unsigned	K3		: 1;
		unsigned	K4		: 1;
    };
};
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf0;
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf1;
extern volatile union ByteType_DisplayBuffer R_Lcd_Buf2;
// extern volatile union ByteType_DisplayBuffer R_Lcd_Buf3;


// ===========LED屏layout映射定义===========
// ===========OLED LAYOUT======================================
//         positive->     pin1    pin2    pin3    pin4    pin5   
// negative     pin1       *       A3      C3      E3      K1    
//              pin2       B3      *       A2      C1      K2    
//              pin3       D3      B2      *       B1      K3    
//              pin4       F3      D2      C2      *       K4    
//              pin5       G3      E2      F2      G2       *     
// ===========================================================
#define	F_SegTubeScan_P12		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf2.A)
#define	F_SegTubeScan_P13		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf2.C)
#define	F_SegTubeScan_P14		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf2.E)
#define	F_SegTubeScan_P15		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf0.K1)

#define	F_SegTubeScan_P21		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.B)
#define	F_SegTubeScan_P23		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.A)
#define	F_SegTubeScan_P24		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf0.C1)
#define	F_SegTubeScan_P25		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf0.K2)

#define	F_SegTubeScan_P31		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.D)
#define	F_SegTubeScan_P32		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.B)
#define	F_SegTubeScan_P34		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf0.B1)
#define	F_SegTubeScan_P35		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf0.K3)

#define	F_SegTubeScan_P41		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.F)
#define	F_SegTubeScan_P42		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.D)
#define	F_SegTubeScan_P43		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.C)
#define	F_SegTubeScan_P45		TRIS_SEGTUBE_P5 = ctrl(R_Lcd_Buf0.K4)

#define	F_SegTubeScan_P51		TRIS_SEGTUBE_P1 = ctrl(R_Lcd_Buf2.G)
#define	F_SegTubeScan_P52		TRIS_SEGTUBE_P2 = ctrl(R_Lcd_Buf1.E)
#define	F_SegTubeScan_P53		TRIS_SEGTUBE_P3 = ctrl(R_Lcd_Buf1.F)
#define	F_SegTubeScan_P54		TRIS_SEGTUBE_P4 = ctrl(R_Lcd_Buf1.G)

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

#define M_ClearPanel R_Lcd_Buf0.buf = R_Lcd_Buf1.buf = R_Lcd_Buf2.buf = 0x00;
#define M_FufillPanel R_Lcd_Buf0.buf = R_Lcd_Buf1.buf = R_Lcd_Buf2.buf = 0xff;
#define M_SegTube_Init    {TRISA |= SEGTUBE_PA; PORTA |= SEGTUBE_PA;TRISB |= SEGTUBE_PB; PORTB |= SEGTUBE_PB;}                 
// ===================================================================


#endif
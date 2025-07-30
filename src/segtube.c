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
#include "segtube.h"
volatile union ByteType_DisplayBuffer R_Lcd_Buf0;
volatile union ByteType_DisplayBuffer R_Lcd_Buf1;
volatile union ByteType_DisplayBuffer R_Lcd_Buf2;
// volatile union ByteType_DisplayBuffer R_Lcd_Buf3;
bit b_SegTubeEn;
bit b_SegTubeScanReq;
const unsigned char numtab[12] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0xFF};  //0~9,blank

void F_SegTubeScan(void)
{
    static u8 R_OLED_Scan_Cnt =0xFF;
    R_OLED_Scan_Cnt++;
    b_SegTubeScanReq = 0;
    switch (R_OLED_Scan_Cnt)
    {
    case 0:
        F_SegTubeScan_P12;
        F_SegTubeScan_P13;
        F_SegTubeScan_P14;
        F_SegTubeScan_P15;
        TRIS_SEGTUBE_P1_ON();
        break;

    case 1:
        F_SegTubeScan_P21;
        F_SegTubeScan_P23;
        F_SegTubeScan_P24;
        F_SegTubeScan_P25;
        TRIS_SEGTUBE_P2_ON();
        break;

    case 2:
        F_SegTubeScan_P31;
        F_SegTubeScan_P32;
        F_SegTubeScan_P34;
        F_SegTubeScan_P35;
        TRIS_SEGTUBE_P3_ON();
        break;

    case 3:
        F_SegTubeScan_P41;
        F_SegTubeScan_P42;
        F_SegTubeScan_P43;
        F_SegTubeScan_P45;
        TRIS_SEGTUBE_P4_ON();
        break;

    case 4: 
        F_SegTubeScan_P51;
        F_SegTubeScan_P52;
        F_SegTubeScan_P53;
        F_SegTubeScan_P54;
        TRIS_SEGTUBE_P5_ON();

    default:
        R_OLED_Scan_Cnt =0xFF;
        break;
    }   
}

//==============================================================
// name:F_ShowSegTube
// input:IconFlag-- Bit0: E icon   Bit1: percent icon bit 2~6: oil cycle icon
//       OilLevel--- oil level: 0~4 level0~level4
//       num ---- num 0~99
//==============================================================
void F_ShowSegTube(u8 IconFlag, u8 OilLevel,u8 num)
{
  
}




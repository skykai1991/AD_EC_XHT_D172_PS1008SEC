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
#include "display_sentence.h"
#include "smoke.h"
#include "usart.h"
u8 R_Light_Idx;
u8 R_Light_Cnt;
bit b_LightPlay_Flag;
u16 R_Light_Time_Cnt = 0;
u8 R_Light_LoopTimes = 0;
u8 R_Light_LoopCnt_ADDR = 0;
extern  const u8* LightTab[16];
// ==================================
void F_PlayLight(u8 LightIdx)
{
	if(b_LightPlay_Flag && R_Light_Idx == 5)return;	//短路灯效中不允许打断；
	b_SegTubeEn = 0;
	M_SegTube_Init
	R_Light_Time_Cnt = 0;
	LED_OFF

	R_Light_Idx = LightIdx;
	R_Light_Cnt = 0;
	b_LightPlay_Flag = 1;
#ifdef _DEBUG_EVENT_
LOG_printf1("F_PlayLight,%d\r\n",R_Light_Idx);
#endif
	// F_PlayLight_8ms();
}
void F_SegTubeDecode(void)
{
	u8 R_Temp0,R_Temp1,R_Temp2;
	R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
	R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
	R_Temp2 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
	if(R_Temp1 == OIL_BY_REG)
    {
		if(R_OilRest > 3*D_FullOil/4) R_Temp1 = 4;
		else if(R_OilRest > 2*D_FullOil/4) R_Temp1 = 3;
		else if(R_OilRest > 1*D_FullOil/4) R_Temp1 = 2;
		else if(R_OilRest >0) R_Temp1 = 1;
		else R_Temp1 = 0;
    }
	   
    if(R_Temp2 == NUM_OFF) R_Temp2 = 0xFF;
    else if(R_Temp2 == NUM_BY_REG)
    {
        R_Temp2 = R_Battery_Percent;
    }			
	F_ShowSegTube(R_Temp0,R_Temp1,R_Temp2);
	b_SegTubeEn = 1;

}
void F_PlayLight_8ms(void)
{
	if((R_Light_Time_Cnt) && (R_Light_Time_Cnt != 0x1fff)) R_Light_Time_Cnt--;
	if(b_LightPlay_Flag && (!R_Light_Time_Cnt))
	{
		u8 R_Temp0,R_Temp1,R_Temp2,R_Temp3;
		switch(*(LightTab[R_Light_Idx] + R_Light_Cnt++))
		{
			case SEGTUBE_LED:
				R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
                R_Light_Time_Cnt = (u16)R_Temp0 << 8 | R_Temp1;
				F_SegTubeDecode();

				R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp2 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp3 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				if(R_Temp0)
				{
					LED_ON(R_Temp0,R_Temp1,R_Temp2,R_Temp3)
				}
			break;

			case SEGTUBE_SET:
				R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Light_Time_Cnt = (u16)R_Temp0 << 8 | R_Temp1;
				F_SegTubeDecode();
			break;

			case SEGTUBE_SCREENOFF:
				R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Light_Time_Cnt = (u16)R_Temp0 << 8 | R_Temp1;
				b_SegTubeEn = 0;
				// M_ClearPanel
				M_SegTube_Init
			break;

			// case NIXTETUBE_FULLSCREEN:
			// 	R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
			// 	R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
			// 	R_Light_Time_Cnt = (u16)R_Temp0 << 8 | R_Temp1;
            //     M_FufillPanel
			// 	b_SegTubeEn = 1;
			// break;
			case FLASHICON_SET:
				R_Temp0 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Temp1 = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
				R_Light_Time_Cnt = (u16)R_Temp0 << 8 | R_Temp1;
				R_Lcd_Buf0.buf = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
			break;

			case LOOP_START:
				R_Light_LoopTimes = *(LightTab[R_Light_Idx] + R_Light_Cnt++);
                R_Light_LoopCnt_ADDR = R_Light_Cnt;
			break;

			case LOOP_END:
                if(--R_Light_LoopTimes)
                {
                    R_Light_Cnt = R_Light_LoopCnt_ADDR;
                }
			break;

			case DISPLAY_END:
				b_LightPlay_Flag = 0;
				b_SegTubeEn = 0;
				LED_OFF
				// M_ClearPanel
				M_SegTube_Init
				if(R_Light_Idx == 1)	// 抽烟灯效结束
				{
					b_SmokeFlag = 0;
				}
			break;
			default:	
			break;
		}
	}
}

void F_StopLight(void)
{
	b_LightPlay_Flag = 0;
	b_SegTubeEn =0;
	R_Light_Time_Cnt = 0;
	M_SegTube_Init
	LED_OFF
}











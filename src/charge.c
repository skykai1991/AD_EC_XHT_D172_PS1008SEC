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
#include "PS1008.h"
#include "common.h"
#include "usart.h"
#include "charge.h"
#include "smoke.h"
#include "display_sentence.h"
bit b_ChargeFlag;

void F_WorkCharge(void)
{
	static u8 R_ChargingTimes = 0;
//---------------------------------------------------------------------
	if(b_ChargeFlag && !b_SmokeFlag)
	{
		if(VADIF)
		{	
			VADIF = 0;

			if((ADCON&0x30) == 0x10) // VBAT
			{
				R_ADC_VBAT = (((VADCH &0x01) <<8)|VADCL);
			}
		}

		if(!b_LightPlay_Flag)
		{
			if(R_Battery_Percent < D_V2T_PCT)
			{
				F_CalculateEneryPercent();
				F_Start_SampBAT();
				if(R_Temp0 > R_Battery_Percent)
				{
					R_Battery_Percent++;
					R_EngCnt = D_SMOKE_PERCENT_TIME;
					if(R_Battery_Percent == 1) 
					{
						PWMCLKEN=1;
						R_ErrFlag.LB = 0;
						if(R_ErrFlag.ErrFlag == 0)   PMOS_CTRL =0;	//	若前面仅因低电把PMOS关了，则重新打开
					}
				}
				R_ChargingTimes = 0;
				F_PlayLight(6);
			}
			else
			{
				if((F_ADC2VBAT(R_ADC_VBAT) > 4200 ) || (++R_ChargingTimes >= D_Time_1PCT))			//10s *12 = 2minutes。充至91%后，每2分钟增加1%至满电；
				{
					R_Battery_Percent++;
					R_EngCnt = D_SMOKE_PERCENT_TIME;
					R_ChargingTimes = 0; 
				}
				if(R_Battery_Percent >= Percent_Full)
				{
					R_Battery_Percent = Percent_Full;
					b_ChargeFlag = 0;
					F_PlayLight(8);
				}
				else 
				{
					F_Start_SampBAT();
					F_PlayLight(6);
				}
			}
			F_PlayLight_8ms();
		}
	}
}
void F_CalculateEneryPercent(void)
{
	R_Temp32 = F_ADC2VBAT(R_ADC_VBAT);
	R_Temp32 = R_Temp32 -V_BATZERO;
	if(R_Temp32 < 2000)
	{
		if(R_Temp32 > (V_FirStage - V_BATZERO))
		{
			R_Temp16_0 = V_FirStage - V_BATZERO;
			R_Temp16_1 = V_BATFULL-V_FirStage;
			R_Temp0 = Percent_Full-Percent_FirStage;
			R_Temp1 = Percent_FirStage;
		}
		else if(R_Temp32 > (V_SecStage - V_BATZERO))
		{
			R_Temp16_0 = V_SecStage - V_BATZERO;
			R_Temp16_1 = V_FirStage-V_SecStage;
			R_Temp0 = Percent_FirStage-Percent_SecStage;
			R_Temp1 = Percent_SecStage;
		}
		else if(R_Temp32 > (V_ThrStage - V_BATZERO))
		{
			R_Temp16_0 = V_ThrStage - V_BATZERO;
			R_Temp16_1 = V_SecStage-V_ThrStage;
			R_Temp0 = Percent_SecStage-Percent_ThrStage;
			R_Temp1 = Percent_ThrStage;
		}
		else 
		{
			R_Temp16_0 = 0;
			R_Temp16_1 = 1;
			R_Temp0 = 0;
			R_Temp1 = 0;
		}
		R_Temp32 = (R_Temp32 - R_Temp16_0) * R_Temp0;
		R_Temp32 = R_Temp32 / R_Temp16_1;
		R_Temp32 += R_Temp1;



        R_Temp0 = R_Temp32 & 0x0ff;
		if(R_Temp0 >= Percent_Full) R_Temp0 = Percent_Full;
	}
	else	R_Temp0 = 0;

}



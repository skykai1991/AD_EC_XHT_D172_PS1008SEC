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
#include "smoke.h"
#include "PS1008.h"
#include "common.h"
#include "display_sentence.h"
#include "usart.h"
#include "setting.h"
#include "charge.h"
#include "PS1008_Core.h"
#include "PS1008_DEF.h"
union ByteType_ErrFlag  R_ErrFlag;
#ifdef _BOMB_INOUT_DETECT_
bit b_Bomb_Online;		// 1: have bomb  0: no bomb
#endif
bit b_SmokeFlag;		// 1:smoking     0:not smoke;
// bit b_HLR_Flag=0;
void F_SMK_Init(void)
{
    AFECLKEN = 1;
	AFEIF0 = AFEIF1 = AFEIF2 = 0;
#ifdef _BOMB_INOUT_DETECT_
    CIGRMVIE=1; //烟弹移除中断使能,如需要烟弹拨出检测，必须要打开烟弹拨出中断，才能产生中断和查询CIGRMVIF
    CIGRMVIF=0;
    CIGINIE=1;  //烟弹插入中断使能,如需要烟弹插入检测，必须要打开烟弹插入中断，才能产生中断和查询CIGINIF
    CIGINIF=0;
	CIGPUR= 1;     //开启上拉电阻做检测 
	b_Bomb_Online = 0;
#else
    CIGRMVIE=0; //烟弹移除中断使能,如需要烟弹拨出检测，必须要打开烟弹拨出中断，才能产生中断和查询CIGRMVIF
    CIGRMVIF=0;
    CIGINIE=0;  //烟弹插入中断使能,如需要烟弹插入检测，必须要打开烟弹插入中断，才能产生中断和查询CIGINIF
    CIGINIF=0;
#endif
    // CHGINIE=1;    //充电器插入中断使能
    // CHGINIF=0;

    // CHGFULLIE=1;  //充满电中断使能
    // CHGFULLIF=0;

    // CHGRMVIE=1; //充电器移除中断使能
    // CHGRMVIF=0;

    KEYIE=0;    //按键中断使能
    KEYIF=0;

    //  CIG2SIE=1;  //烟弹插拔2S中断使能
    //  CIG2SIF=0;

    //  KEY2SIE=1;  //按键2S的中断使能
    //  KEY2SIF=0;

    // CAP2SIE=1; //吸烟2S的中断使能
    // CAP2SIF=0; 

    // UVPIE=1;      //欠压保护中断
    // UVPIF=0;

    // SMKSTARTIE=1; //吸烟启动中断
    // SMKSTARTIF=0;
    // SMKTMOIE  =1; //吸烟超时中断
    // SMKTMOIF  =0;

    // SMKOVERIE=1; //吸烟完成中断
    // SMKOVERIF=0;

	PDRV_SYNC = 0;			//若要支持外扩MOS，PDRV_SYNC = 1;PB6设置输出；
    PWMCLKEN=1;
	F_UVP_VOLT_Setting(UVL_3_3V);
//设置输出电压或功率
#ifdef  _SMOKE_CTRL_CONST_VOLTAGE_
	R_Temp16_0 = MTP_INFO_RD(0x0B);
    CONSET = ((u32)D_CV_SET / R_Temp16_0) / 2;
#endif
#ifdef  _SMOKE_CTRL_CONST_RMS_
	R_Temp16_0 = MTP_INFO_RD(0x0B);
    R_Temp32 = (u32)D_RMS_SET / R_Temp16_0 / 2;
    R_Temp32 = R_Temp32 * R_Temp32 >>8;
    CONSET = R_Temp32 + 2;
#endif
#ifdef  _SMOKE_CTRL_CONST_POWER_
   R_Temp16_0 = MTP_INFO_RD(0x0C);
    CONSET = ((u32)D_CP_SET * R_Temp16_0 +5000)/10000;
#endif
    // LOG_printf1("CONSET = %d \n",CONSET);
	PMOS_CTRL = 0;
	// b_HLR_Flag = 0;
    SCPIE = 0;    //短路保护中断
    SCPIF = 0;
    OCPIE = 0;
    OCPIF = 0;
	

}
void F_AFE_Event(void)
{
	//AFEIF0 查询处理
	if(AFEIF0)
	{
		if (SCPIF)
		{
			SCPIF = 0;
			F_PlayLight(5);
#ifdef _DEBUG_EVENT_
LOG_printf0("short before smk\n");
#endif
			return;
		}

		if(OCPIF)
		{
			OCPIF = 0;
			F_PlayLight(5);
			return;
		}
		
		if(UVPIF)
		{
			UVPIF = 0;
			R_Battery_Percent = 0;
			b_SmokeFlag = 0;
			PWMCLKEN=1;
			PMOS_CTRL = 1;
			// if(R_ErrFlag.LB == 0)
			// {
			R_ErrFlag.LB = 1;
			F_PlayLight(4);
			// }
#ifdef _DEBUG_EVENT_
LOG_printf0("lowbat\n");
#endif
		}
	// 	else if (OTPIF)
	// 	{
	// 		AFEIF0 = 0;
	// 		b_SmokeFlag = 0;
	// 		// F_PlayLight(0);
	// #ifdef _DEBUG_EVENT_
	//    LOG_printf0("over temperate\n");
	// #endif
	// 	}
		else if(SMKTMOIF)
		{
			SMKTMOIF = 0;
			b_SmokeFlag = 0;
			// PWMCLKEN=1;
			// PMOS_CTRL = 1;
			F_PlayLight(3);
#ifdef _DEBUG_EVENT_
LOG_printf0("smk overtime\n");
#endif
		}
		else if(SMKOVERIF)
		{
			SMKOVERIF = 0;
// 			if(b_SmokeFlag && (b_PowerOn_Flag != 0x5A))
// 			{
// 			// F_PlayLight(2);
// 				R_Light_LoopTimes = 1;
// 				b_SmokeFlag = 0;
// #ifdef _DEBUG_EVENT_
// LOG_printf0("MIC OFF\n");
// #endif
// 			}

		}
		else if(CAPSTARTIE) 
		{
			CAPSTARTIE = 0;
// #ifdef _DEBUG_EVENT_
// LOG_printf0("SMKSTARTIF\n");
// #endif

#ifdef _BOMB_INOUT_DETECT_
			if(b_Bomb_Online == 0)		//吸烟前开路
			{
				F_PlayLight(9);		//开路灯效
				PMOS_CTRL = 1;
				R_ErrFlag.OPEN = 1;
				return;
			}
			else
			{
				R_ErrFlag.OPEN = 0;
				if(R_ErrFlag.ErrFlag == 0 )
				{
				    PMOS_CTRL = 0;
				}
			}

#endif
			if(R_ErrFlag.LB)		//低电
			{
			    F_PlayLight(4);
				return;
			}
			else if (R_ErrFlag.HZ || R_ErrFlag.LZ)		//高阻或低阻
			{
				PMOS_CTRL = 0;
				R_ErrFlag.HZ = 0;
				R_ErrFlag.LZ = 0;
			}
		}
	}
	
//AFEIF1 查询处理
	if(AFEIF1)
	{
		if(CHGINIF)
		{
			CHGINIF =0;
			Recharge(0);
			if(R_Battery_Percent < Percent_Full)	//充电插入
			{
				b_ChargeFlag = 1;
				if(!b_SmokeFlag) F_PlayLight(6);
				F_Start_SampBAT();
			}
			else									//插入充满
			{
				R_Battery_Percent = Percent_Full;
				b_ChargeFlag = 0;
				if(!b_SmokeFlag) F_PlayLight(8);
			}	
		}
		else if(CHGFULLIF) //充满 
		{
			CHGFULLIF =0;
			Recharge(1);
			if(b_ChargeFlag)
			{
				b_ChargeFlag = 0;
				R_Battery_Percent = Percent_Full;
				if(!b_SmokeFlag) F_PlayLight(8);				
			}
		}
		else if(CHGRMVIF) // USB拔出
		{
			CHGRMVIF =0;
			Recharge(0);
			b_ChargeFlag =0;
			if(!b_SmokeFlag) F_PlayLight(7);
		}

		if(CIGINIF)
		{
			CIGINIF = 0;
			CIGPUR= 0;  
#ifdef _BOMB_INOUT_DETECT_
			b_Bomb_Online = 1;
			// F_PlayLight(0);
// #ifdef _DEBUG_EVENT_
// LOG_printf0("BOMB IN\n");
// #endif
#endif
		}
		else if(CIGRMVIF)
		{
			CIGRMVIF = 0;
			CIGPUR= 1; 
#ifdef _BOMB_INOUT_DETECT_
			b_Bomb_Online = 0;
			// F_PlayLight(0);
// #ifdef _DEBUG_EVENT_
// LOG_printf0("BOMB OUT\n");
// #endif
#endif
		}

		if(KEYIF)
		{
			KEYIF = 0;
// 			if(b_SmokeFlag && PB0)
// 			{
// 			// F_PlayLight(2);
// 				R_Light_LoopTimes = 1;
// 				b_SmokeFlag = 0;
// #ifdef _DEBUG_EVENT_
// LOG_printf0("KEY OFF\n");
// #endif
// 			}
// 			else if(!(b_SmokeFlag || PB0))
// 			{
// 				b_SmokeFlag = 1;
// #ifdef _RV_DET_SMKING_
// 				b_CheckRing_Flag = 0;
// #endif
// 				F_PlayLight(1);
// #ifdef _DEBUG_EVENT_
// LOG_printf0("KEY ON\n");
// #endif
// 			}
		}
	}

//AFEIF2 查询处理2秒计时事件
// 	if(AFEIF2)
// 	{
// 		if(CIG2SIF || KEY2SIF ||CAP2SIF)
// 		{
// 			CIG2SIF = KEY2SIF = CAP2SIF = 0;
// #ifdef _DEBUG_EVENT_
// 	LOG_printf0("2S time\n");
// #endif
// 		}
// 	}
}
void F_WorkSmoke(void)
{
	if(b_SmokeFlag/* && b_Bomb_Online */)
	{
//吸烟油量计算
        if(R_OilCnt) R_OilCnt--;
		if(!R_OilCnt)
		{
			R_OilCnt =D_SMOKE_IOL_TIME;
			if(R_Oil_Percent)R_Oil_Percent--;
		}
//吸烟电量计算 每1%吸烟时长5s，电量1%后由欠压判断电量转为0%
		if(R_EngCnt) R_EngCnt--; 
		if(!R_EngCnt)
		{
			if(R_Battery_Percent > 1)R_Battery_Percent--;
			R_EngCnt = D_SMOKE_PERCENT_TIME;
			u8 i = 0;
			u8 j = R_Battery_Percent;
			while(j>=10)
			{
				j -=10;
				i++;
			}
			if(i == 0)i=10;     //十位灭0处理；
			M_Show_Tenbit(i)
			M_Show_Unitbit(j)
		}
	}


}

/*这段代码是一个用于检测电子烟设备中负载电阻值的函数F_SmokingRV_Det。
它主要用于在吸烟过程中检测负载的电阻值，以判断负载状态（如开路、低阻或高阻），
并根据检测结果采取相应的措施。*/
void F_SmokingRV_Det(void)
{
#ifdef _RV_DET_SMKING_
//负载阻值检测；
	if(b_SmokeFlag)
	{
		if(b_CheckRing_Flag)
		{
			if(VADIF)		
			{						//检测MOS电流和OUT电压
				if((ADCON & 0x30) == 0x00)
				{
					vu16  R_VADC_Vout,R_CADC_MOS,R_KMOS;
					unsigned long Res_OUT;
					VADIF = 0;
					CADIF = 0;
					b_CheckRing_Flag = 0;
					R_VADC_Vout =(((VADCH&0x01) <<8)|VADCL);//读取ADC采集值  >>1
					R_CADC_MOS =((CADCH &0x01)  <<8)|CADCL;//读取流过PMOS的电流值
					// if(!(R_VADC_Vout && R_CADC_MOS)) return;
					if(R_CADC_MOS < 50)
					{					//负载开路
	#ifdef _DEBUG_EVENT_
	LOG_printf0("load open\r\n");	
	#endif
					}
					else if(R_VADC_Vout > 50)		//无极小VOUT,ADC正常
					{
						R_Temp16_0 = MTP_INFO_RD(0x0B);
						R_Temp16_1 = MTP_INFO_RD(0x0D);
						R_KMOS = (unsigned long)R_Temp16_0*1000/R_Temp16_1;
						Res_OUT=(unsigned long)R_VADC_Vout*R_KMOS/R_CADC_MOS;//计算当前外部电阻值(单位：mΩ)
		// #ifdef _DEBUG_EVENT_
		// LOG_printf3("V=%d,I=%d,R=%d\r\n",R_VADC_Vout,R_CADC_MOS,Res_OUT);
		// #endif
						if(Res_OUT < 900)				//低阻
						{
							b_SmokeFlag = 0;
							PWMCLKEN=1;
							PMOS_CTRL = 1;
							R_ErrFlag.LZ = 1;
							// b_HLR_Flag = 1;
							F_PlayLight(5);
	#ifdef _DEBUG_EVENT_
	LOG_printf3("V=%d,I=%d,R=%d\r\n",R_VADC_Vout,R_CADC_MOS,Res_OUT);
	#endif
							return;
						}
						#if 0
						else if(Res_OUT > 1500)			//高阻
						{
							b_SmokeFlag = 0;
							PWMCLKEN=1;
							PMOS_CTRL = 1;
							R_ErrFlag.HZ = 1;
							// b_HLR_Flag = 1;
							F_PlayLight(9);
	#ifdef _DEBUG_EVENT_
	LOG_printf3("V=%d,I=%d,R=%d\r\n",R_VADC_Vout,R_CADC_MOS,Res_OUT);
	#endif
							return;
						}
						#endif

					}
					AFECLKEN      =1;   //ADC采集必须打开AFECLK******
					VADIF = 0;
					CADIF = 0;
    				ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VBAT | ADCSP_15MS | ADCMUX_V1C1 | ADC_GO;
					b_CheckRing_Flag = 1;

				}
				else if((ADCON & 0x30) == 0x10)		//检测VBAT电压
				{
					vu16  R_VADC_BAT;
					VADIF = 0;
					b_CheckRing_Flag = 0;
					R_VADC_BAT =(((VADCH&0x01) <<8)|VADCL);//读取ADC采集值  >>1
					#if 0
					if (F_ADC2VBAT(R_VADC_BAT) < 3000)		//吸烟中低电
					{
		#ifdef _DEBUG_EVENT_
		LOG_printf0("lowbat\r\n");
		#endif
					}
					#endif
					

					VADIF = 0;
					CADIF = 0;
					ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VOUT | ADCSP_15MS | ADCMUX_V0C0 | ADC_GO;
					b_CheckRing_Flag = 1;
				}
				else
				{
					AFECLKEN      =1;   //ADC采集必须打开AFECLK******
					VADIF = 0;
					CADIF = 0;
					ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VOUT | ADCSP_15MS | ADCMUX_V0C0 | ADC_GO;
					b_CheckRing_Flag = 1;
				}
			}
		}
		else
		{
				AFECLKEN      =1;   //ADC采集必须打开AFECLK******
				VADIF = 0;
				CADIF = 0;
				ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VOUT | ADCSP_15MS | ADCMUX_V0C0 | ADC_GO;
				b_CheckRing_Flag = 1;
		}
	}
#endif
}
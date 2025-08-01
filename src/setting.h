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
#ifndef __SETTING_H__
#define __SETTING_H__

// #define _DEBUG_EVENT_		//打开debug 打印事件信息模式
// #define _DEBUG_ONLINE_		//打开在线调试命令
//以下三种输出模式，三选一；
#define _SMOKE_CTRL_CONST_VOLTAGE_	//恒压输出
// #define _SMOKE_CTRL_CONST_RMS_			//恒有效输出
// #define _SMOKE_CTRL_CONST_POWER_		//恒功率输出

#ifdef  _SMOKE_CTRL_CONST_VOLTAGE_
	#define D_CV_SET		2900000		//恒压值设置，3.2V对应3200000
	#define D_CV_SET_1		2800000		
	#define D_CV_SET_2		2900000		
	#define D_CV_SET_3		3000000		
	#define D_CV_SET_PRE	1800000		
	#define  OPMOD_SET  OPMOD_CONST_VOLTAGE
#endif
#ifdef  _SMOKE_CTRL_CONST_RMS_
	#define D_RMS_SET	3200000		//恒有效值设置，3.2V对应3200000
	#define  OPMOD_SET  OPMOD_CONST_RMS
#endif
#ifdef  _SMOKE_CTRL_CONST_POWER_
	#define D_CP_SET	65		//恒功率值设置，6.5w对应65
	#define  OPMOD_SET  OPMOD_CONST_POWER
#endif

#define CONFIG0_SET  (DEAFULT_CFG0 + FINTOSC_DIV1 + IRST_EN + FCPU_4T + LVR_EN + LVR_22V)
#define CONFIG1_SET  (DEAFULT_CFG1 + INPUTLEVEL_SMT + ENCRYPT_DIS + DBG_IIC_DIS + DBG_UART_EN + POR_WDT_246MS)
#define CONFIG2_SET  (DEAFULT_CFG2 + OPMOD_SET + UARTBR_1M + CHGFULL_4V2 + CHGCUR_500MA)
#define CONFIG3_SET  (DEAFULT_CFG3 + CHG_SMK_DIS + MIC_CAP + OTPTEMP_165)
#define CONFIG4_SET  (DEAFULT_CFG4 + CAP_NORMAL + SMKOT_8S + CAPSENSITIVE_32)



//以下配置烟弹插拨功能使能,定义则使能，如果吸烟开路报警，需要定义；
#define  _BOMB_INOUT_DETECT_

//以下配置吸烟中阻值检测和电压检测；
#define _RV_DET_SMKING_
//以下配置吸烟电量几少减1%；
#define D_SMOKE_PERCENT_TIME	D_8ms_5S
#define D_SMOKE_IOL_TIME	    11100/8    // 1% 的油量

//以下上电及充电时电池电量曲线；
#define V_WORKVOLTAGE    3200

#define V_BAT2VCC		 40	         //BAT与VCC串联电阻压降补偿

#define V_BATFULL        4120       // 满电电压 4.12V - 99%
#define Percent_Full     100			// 满电电量百分比

#define V_FirStage       3950       //一档电压3.95V - 90%
#define Percent_FirStage 90			//一档电量百分比

#define V_SecStage       3650       //二档电压V3.65V - 10%
#define Percent_SecStage 10			//二档电量百分比

#define V_ThrStage       3300       //三档电压3.30V - 1%
#define Percent_ThrStage 1			//三档电量百分比

#define V_BATZERO        V_WORKVOLTAGE //0电量电压

//充电模式电压算电量与时间算电量门槛值
#define  D_V2T_PCT	90		//90%电量前，充电时以电压计算电量，90%电量以上，以时间计算电量；

//时间计算电量时，每增加1%需要的计时时间
#define D_Time_1PCT		12		//6*10s = 2分钟加1%

//满油秒数定义，Unit:秒；
#define D_FullOil 2000			

#endif
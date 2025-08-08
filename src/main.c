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
/*===========================================================================================================
//***********************************************************************************************/
#include "PS1008.h"
#include "PS1008_DEF.h"
#include "setting.h"
#include <stdio.h>
#include "charge.h"
#include "usart.h"
#include "common.h"
#include "display_sentence.h"
#include "smoke.h"
#include "PS1008_Core.h"
#include "mic.h"
#include "key.h"
//***************************************************************************************************
__CONFIG(CONFIG0_SET);
__CONFIG(CONFIG1_SET);
__CONFIG(CONFIG2_SET);
__CONFIG(CONFIG3_SET);
__CONFIG(CONFIG4_SET);

//==============================================================================================
// ----Function: 主程序
// --Parameters: None
// -----Returns: None
//---------Note:
//==============================================================================================
void main(void)
{
   F_System_Init();
   Timer0_Init();
   Timer1_Init();
   F_SMK_Init();

   __delay_ms(100);
   //初始化油量
   R_Oil_Percent = 100;
   R_OilCnt = D_SMOKE_IOL_TIME;
   //计算电池电压和电量
   F_VADC_Sample_VBAT();
   F_CalculateEneryPercent();
   R_Battery_Percent = R_Temp0;
   R_EngCnt = D_SMOKE_PERCENT_TIME;
   if(CHGENS&&CHGFULLS==0)
   {
      b_ChargeFlag = 1;
      blockFlag =0;
		F_PlayLight(6);
		F_Start_SampBAT();
      b_FirstUsbInFlag =0;
      b_PowerOn_Flag = 0; //上电标志
   }
   else
   {
      F_PlayLight(0);//上电显示  
      blockFlag =1;
      b_FirstUsbInFlag =1;
      b_PowerOn_Flag = 1; //上电标志
   }
   b_PowerOn_Flag = 1; //上电标志
	R_Sleep_Off = D_8ms_2S;
   R_ErrFlag.ErrFlag = 0;
      
   OSCCON = FINTOSC_1 + CKOE_DIS + OSC_HIGH;
   WDTEN = 1;
   M_SMKORIG
   if(CIGN) {b_Bomb_Online =1; CIGPUR =0;}
   else {b_Bomb_Online =0;CIGPUR=1;}
   
   GIE = 1;
   while(1)
   {
      CLRWDT();
      if(b_T1_Flag)//500us 定时
      {
         b_T1_Flag = 0;
         M_SegTube_Init
         b_SegTubeScanReq = 1;
         if(b_SegTubeEn && b_SegTubeScanReq)   F_SegTubeScan();  
         F_MICInput();
         F_SmokingRV_Det();
      }
      if(b_T8ms_Flag)//8ms event
      {
         b_T8ms_Flag = 0;
         F_KEYInput();
         F_WorkSmoke();
         F_PlayLight_8ms();
         F_WorkCharge();
         if(R_Sleep_Off)R_Sleep_Off--;
         if(b_SmokeShortDelayTime)b_SmokeShortDelayTime--;
         if(R_InputKeyRepeatTime)R_InputKeyRepeatTime--;
      }
      F_AFE_Event();
      F_Work_PowerOff();
   }
}

//中断服务函数
void interrupt ISR(void)
{
#if 0
   if(AFEIE0 & AFEIF0)
   {

   }
   if(AFEIE2 & AFEIF2)
   {

#ifdef _DEBUG_ONLINE_
   if((RCIE==1)&&(RCIF==1)) //UART接收的中断
   {
      RCIF=0;
      F_UART_ReceiverISR();
   }
#endif

   }
#endif
   if((T0IE == 1)&&(T0IF == 1)) //timer0 的中断
   {
      T0IF = 0;
      T0IE = 0;
   } 

   if((T1IE == 1)&&(T1IF == 1)) //timer1 的中断
   {
      T1IF = 0;
      b_T1_Flag = 1;
      if(!(R_T1_cnt++ & 0x0F)) b_T8ms_Flag = 1;
   } 

   if((PBIE == 1)&&(PBIF == 1)) //PortB 的中断
   {
      PBIF =0;
   }
}


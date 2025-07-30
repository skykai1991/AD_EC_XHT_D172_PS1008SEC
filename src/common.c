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
#include "common.h"
#include "usart.h"
#include "charge.h"
#include "display_sentence.h"
#include "PS1008.h"
#include "PS1008_DEF.h"
#include "HardwareDef.h"
#include "setting.h"
u8  R_T1_cnt = 0;
/*电量相关变量*/
u8 R_Battery_Percent;//转成百分比的电池电量值,最大100, 最小0
u16 R_EngCnt;        //口数对应电量
/*油量相关变量*/
u8 R_Oil_Percent;//转成百分比的油量值,最大100, 最小0
u16 R_OilCnt;        //口数对应油量

u16 R_ADC_VBAT;//采集VBAT 的ADC 值
u32 R_Temp32;
u16 R_Temp16_0;
u16 R_Temp16_1;
u8 R_Temp0;
u8 R_Temp1;

u8 R_Mode;//当前模式
#ifdef _RV_DET_SMKING_
bit b_CheckRing_Flag;
#endif
bit b_PowerOn_Flag;
bit b_T1_Flag;
bit b_T8ms_Flag;

u16 R_Sleep_Off;//灯效显示结束后等待睡眠时间


void F_System_Init(void)
{
     /* GPIO初始化 PA*/
    TRISA  = SEGTUBE_PA | PB1_SMT_37 | UARTMUX_PB12; //bit[4:0]1：输入 0：输出  bit7:PB1 SMT  BIT6:UART MUX
    PORTA  = SEGTUBE_PA ; //1：高电平 0低电平

    /* GPIO初始化 PB*/
    TRISB   = SEGTUBE_PB | (1 << BIT_VPP) | (0 << BIT_CLK) | (1 << BIT_DAT) | (1 << BIT_KEY) | (1 << BIT_OUT); //PB口输入1,输出0 模式设置
    PORTB   = SEGTUBE_PB | (1 << BIT_VPP) | (0 << BIT_CLK) | (1 << BIT_DAT) | (1 << BIT_KEY) | (0 << BIT_OUT); //PB口电平输出
    PBPU    =  0                          | (0 << BIT_CLK) | (0 << BIT_DAT) | (0 << BIT_KEY) | PB7OUT_PU_DIS | PB7OUT_PD_DIS;    //PB0固定300K上拉
                                                    //PB bit[6:1]1：打开上拉 0：关闭上拉 
                                                    //PB7可选上下拉；
                                                    //CLK/DAT在有外部下拉时，不用开内部上拉；
}
void F_Work_PowerOff(void)
{
    if((R_Sleep_Off || b_SmokeFlag || b_ChargeFlag || b_LightPlay_Flag || SMKINGS)) return;
    if(b_PowerOn_Flag == 1)
    {
        b_PowerOn_Flag = 0;
        //重新计算电池电压和电量
        F_VADC_Sample_VBAT();
        F_CalculateEneryPercent();
        R_Battery_Percent = R_Temp0;
    }

#ifdef _DEBUG_EVENT_
     LOG_printf0("power off\n");
#endif
    // ledRedFlag = 0;
//--------------------------------------------------
    T0CON = 0;
    TMR0CLKEN = 0;

    T1CON0 = 0;
    TMR1CLKEN = 0;
//--------------------------------------------------
    AFECLKEN = 1;

    CHGINIE=1;    //充电器插入中断使能
    CHGINIF=0;
    CHGRMVIE=1; //充电器移除中断使能
    CHGRMVIF=0;

    KEYIE=0;    //按键中断使能
    KEYIF=0;

    CAPSTARTIE=1; //吸烟启动中断
    SMKSTARTIF=0;

#ifdef _BOMB_INOUT_DETECT_
    CIGRMVIE=1; //烟弹移除中断使能,如需要烟弹拨出检测，必须要打开烟弹拨出中断，才能产生中断和查询CIGRMVIF
    CIGRMVIF=0;
    CIGINIE=1;  //烟弹插入中断使能,如需要烟弹插入检测，必须要打开烟弹插入中断，才能产生中断和查询CIGINIF
    CIGINIF=0;
#else
    CIGRMVIE=0; //烟弹移除中断使能,如需要烟弹拨出检测，必须要打开烟弹拨出中断，才能产生中断和查询CIGRMVIF
    CIGRMVIF=0;
    CIGINIE=0;  //烟弹插入中断使能,如需要烟弹插入检测，必须要打开烟弹插入中断，才能产生中断和查询CIGINIF
    CIGINIF=0;
#endif

    CHGFULLIE=0;  //充满电中断使能
    CHGFULLIF=0;

    UVPIE=0;      //欠压保护中断
    UVPIF=0;

    SMKTMOIE  =0; //吸烟超时中断
    SMKTMOIF  =0;

    SMKOVERIE=0; //吸烟完成中断
    SMKOVERIF=0;

    TRISA &= ~SEGTUBE_PA;
    PORTA &= ~SEGTUBE_PA;
    TRISB &= ~SEGTUBE_PB;
    PORTB &= ~SEGTUBE_PB;
    
    UARTCON = 0;
    RCIE = 0;
    RCIF = 0;
    UARTCLKEN = 0;
    WUBCON = WAKEUP_PB_PIN;
    PBIE = 1;
    PBIF = 0;
    R_Sleep_Off = PORTB;
    WDTEN = 0;
#ifdef _DEBUG_ONLINE_
    // TRISB1  = 1;
    // PUB1  = 0;
    WUBCON = WAKEUP_PB_PIN;
    PBIE = 1;
    PBIF = 0;
    R_Sleep_Off  = PORTB;
#endif
    CLRWDT();

    SLEEP_PWOFF();
    Timer0_Init();
    Timer1_Init();

    CHGINIE = CHGRMVIE = CHGFULLIE = 0;
    CAPSTARTIE = 0;
#ifdef _DEBUG_ONLINE_
    PBIE = 0;
    PBIF = 0;
    b_UartRecevirFinish = 0;
    b_Uart_StartFlag = 0;
#endif
// #ifdef _DEBUG_EVENT_
//     LOG_printf0("wakeup\n");
// #endif

    R_Sleep_Off = D_8ms_600ms; 
    WDTEN = 1;
    CLRWDT();

}


/*==================================T0 8ms计时===================================================

4T模式下定时：  Time = （PR0+1）*{PS2:PS0}*4/Fsys；//TMR0的初值为0时
	                                Time = （0XFF-[TMR0]+1）*{PS2:PS0}*4/Fsys；//TMR0设定初值
2T模式下定时：  Time = （PR0+1）*{PS2:PS0}*2/Fsys；//TMR0的初值为0时
			 Time = （0XFF-[TMR0]+1）*{PS2:PS0}*2/Fsys；//TMR0设定初值

====================================T0 8ms计时===================================================*/
#define Freq_Timer0     125 //8ms
void Timer0_Init(void)
{  
   	TMR0CLKEN = 1;
	T0CON = BUZZER_DIS + T0CK_CPU + T0SE_RISEEDGE + PSA_EN + T0CKPS_DIV256;
	PR0 = _XTAL_FREQ/4/256/Freq_Timer0;
	TMR0 = 0;
	// T0IF = 0;
	T0IE = 0;
}

/*==================================T1 1ms计时===================================================

4T模式下定时：  Time = （PR0+1）*{PS2:PS0}*4/Fsys；//TMR0的初值为0时
	                                Time = （0XFF-[TMR0]+1）*{PS2:PS0}*4/Fsys；//TMR0设定初值
2T模式下定时：  Time = （PR0+1）*{PS2:PS0}*2/Fsys；//TMR0的初值为0时
			 Time = （0XFF-[TMR0]+1）*{PS2:PS0}*2/Fsys；//TMR0设定初值

====================================T1 1ms计时===================================================*/
#define Freq_Timer1     1000 //1ms
void Timer1_Init(void)
{
    TMR1CLKEN  = 1;
    TMR1H       = 0X00;
    TMR1L       = 0X00;
    PR1H        = (_XTAL_FREQ/4/8/Freq_Timer1-1) >> 8;
    PR1L        = (_XTAL_FREQ/4/8/Freq_Timer1-1) & 0xFF;;

	T1CON0 = T1CK_FCPU + T1SE_RISEEDGE + T1SYNC_EN + TM1CS_T1CK + T1CKPS_DIV8 + TM1_ON; 
	T1CON1 &= 0xF0;
    T1CON1 |= T1MOD_TIMER + T1IF_TIMER + T1OS_CONTI + INT0EDGE_RISE + INT0MAP_PA0;

	// T1IF = 0;
	T1IE = 1;
    R_T1_cnt = 0;
}

unsigned int F_ADC2VBAT(unsigned int voltage){
    R_Temp16_0 = MTP_INFO_RD(0x0A);
    return ((unsigned long int)voltage*R_Temp16_0)/1000;
}




/* ============================================== VOUT =======================================================
ADC_MODE[1:0]    ：VADC1跟随VADC0同步采样, CADC1 跟随CADC0同步采样，并产生中断VADCIF和CADCIF；
VADC1IN_MUX[1:0] ：VOUT
AD_FAST          ：采集时间为15ms;
ADC_MUX[1:0]     ：VADC0和CADC0
电压系数4.0V     : 
IC1
0.008609
VBAT = ((unsigned long int)Result*8609)/1000 +170;
============================================== VOUT =======================================================*/
void F_VADC_Sample_VOUT(void)
{
    u16 R_ADC_Vout;//采集Vout 的ADC 值
    AFECLKEN      =1;   //ADC采集必须打开AFECLK******
    ADCON = ADCMOD_DUAL_FOLLOW | VDAC1_SEL_VOUT | ADCSP_15MS | ADCMUX_V0C0;
    R_ADC_Vout = F_VADC_Sample();
}



/* ============================================== VBAT =======================================================
ADC_MODE[1:0]    ：VADC1 当GO等于1启动一次采集，GO结束后产生中断VADIF；CADC1 跟随CADC0同步采样，产生中断CADIF
VADC1IN_MUX[1:0] ：VBAT
AD_FAST          ：采集时间为15ms;
ADC_MUX[1:0]     ：VADC1和CADC1
============================================== VBAT =======================================================*/
void F_VADC_Sample_VBAT(void)   //阻塞式采集VBAT
{
    AFECLKEN      =1;   //ADC采集必须打开AFECLK******
    ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VBAT | ADCSP_15MS | ADCMUX_V1C1;
    R_ADC_VBAT = F_VADC_Sample();

// #ifdef _DEBUG_EVENT_
//     LOG_printf1("VBAT_15ms =  %d %d\r\n",R_ADC_VBAT);         //打印AD转换数据  
// #endif
}

unsigned int F_VADC_Sample(void)
{
    // unsigned char  j;
    R_Temp16_0       = 0;
    for(R_Temp0 = 0; R_Temp0 < 4; R_Temp0++)
    {
        GO=1;
        while(VADIF==0)
        {}
        VADIF=0;
// #ifdef _DEBUG_EVENT_
//    LOG_printf1("adc = %d \n",(((VADCH &0x01) <<8)|VADCL));
// #endif
        R_Temp16_0     += (((VADCH &0x01) <<8)|VADCL);//读取ADC采集值  >>1
    }
    R_Temp16_0 = R_Temp16_0>>2;
     return R_Temp16_0;
}



//  ============================================== VBAT =======================================================
void F_Start_SampBAT(void)   //非阻塞式采集VBAT
{
    GO = 0;
    VADIF = 0;
    AFECLKEN      =1;   //ADC采集必须打开AFECLK******
    ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VBAT | ADCSP_15MS | ADCMUX_V1C1;
	GO=1;
}
//  ============================================== VIN =======================================================
void F_Start_SampVIN(void)   //非阻塞式采集VBIN
{
    GO = 0;
    VADIF = 0;
    AFECLKEN      =1;   //ADC采集必须打开AFECLK******
    ADCON = ADCMOD_CADC_FOLLOW | VDAC1_SEL_VIN | ADCSP_15MS | ADCMUX_V1C1;
	GO=1;
}




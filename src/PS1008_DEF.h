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
// Ver: V1.0.1   2024-12-11  Kenny Yeh   1.修正CHG_SMK_EN 定义错误；
// Ver: V1.0.2   2024-12-12  Kenny Yeh   1. 修正UARTBR_115200/1M 定义错误；
//===========================================================================================================
#ifndef __PS1008_DEF_H
#define __PS1008_DEF_H
//======= CONFIG0 define============
#define DEAFULT_CFG0			0x3F00
#define FINTOSC_DIV1			(0x07 << 5)		//内部RC分频
#define FINTOSC_DIV2			(0x06 << 5)
#define FINTOSC_DIV4			(0x05 << 5)
#define FINTOSC_DIV8			(0x04 << 5)
#define FINTOSC_DIV16			(0x02 << 5)
#define IRST_EN					0x10			//非法指令使能
#define IRST_DIS				0x00
#define FCPU_2T					0x00			//CPU指令周期
#define FCPU_4T					0x08
#define LVR_EN					0x04			//LVR使能
#define LVR_DIS					0x00
#define	LVR_22V					0x01			//LVR电压选择
#define	LVR_24V					0x02
#define	LVR_28V					0x03
#define	LVR_RESVERED			0x00
//======= CONFIG1 define============
#define DEAFULT_CFG1			0x3F00
#define INPUTLEVEL_SMT			0x80	//电平选择SMT or TTL	
#define INPUTLEVEL_TTL			0x00	
#define ENCRYPT_EN				0x00	//代码加密使能
#define ENCRYPT_DIS				0x40	
#define DBG_IIC_EN				0x20	//IIC调试使能
#define	DBG_IIC_DIS				0x00	
#define DBG_UART_EN				0x10	//UART调试使能
#define	DBG_UART_DIS			0x00	
// #define	WDTCFG_EN				0x08	//禁止在配置字中开启WDT
// #define	WDTCFG_DIS				0x00	
#define POR_WDT_31MS			0x07	//上电复位 = WDT = 62.24ms
#define POR_WDT_4MS				0x06	//上电复位 = WDT = 62.24ms
#define POR_WDT_246MS			0x05	//上电复位 = WDT = 62.24ms
#define POR_WDT_62MS			0x04	//上电复位 = WDT = 62.24ms
#define POR_15CLK_WDT_31MS		0x03	//上电复位 = 15clk，WDT = 62.24ms
#define POR_15CLK_WDT_4MS		0x02	//上电复位 = 15clk，WDT = 62.24ms
#define POR_15CLK_WDT_246MS		0x01	//上电复位 = 15clk，WDT = 62.24ms
#define POR_15CLK_WDT_62MS		0x00	//上电复位 = 15clk，WDT = 62.24ms

//======= CONFIG2 define============
#define DEAFULT_CFG2			0x3F20
#define OPMOD_CONST_VOLTAGE		(0x00 << 6)		//输出模式恒压
#define OPMOD_CONST_RMS			(0x01 << 6)		//恒有效值
#define OPMOD_CONST_POWER		(0x02 << 6)		//恒功率
// #define LOCK_KEY				(0x00 << 4)		//按键童锁
// #define	LOCK_KEY_SMK			(0x01 << 4)		//按键、吸烟童锁
// #define	LOCK_KEY_SMK_BOM		(0x02 << 4)		//按键、吸烟、烟弹童锁
// #define	LOCK_DIS				(0x03 << 4)		//无童锁
#define	UARTBR_115200			0x00			//调试模式UART波特率
#define	UARTBR_1M				0x08
#define CHGFULL_4V2				0x00			//充满电压
#define CHGFULL_4V1				0x04
#define CHGCUR_300MA			0x00			//充电电流
#define CHGCUR_500MA			0x01
//======= CONFIG3 define============
#define DEAFULT_CFG3			0x3F72
#define	CHG_SMK_EN				0x80			//边充边吸使能
#define	CHG_SMK_DIS				0x00
#define	MIC_CAP					0x04			//空咪
#define	MIC_SWITCH				0x00			//开关咪
#define	OTPTEMP_165				0x01			//过温保护阈值
#define OTPTEMP_175				0x00
//======= CONFIG4 define============
#define DEAFULT_CFG4			0x3F20
#define LED_BY_HW				0x40			//硬件控制LED
#define LED_BY_MCU				0x00			//MCU控制LED
#define	CAP_INVERT				0x10			//反向空咪
#define	CAP_NORMAL				0x00			//正向空咪
#define SMKOT_12S5				(0x00 << 2)		//过吸时间
#define SMKOT_10S				(0x01 << 2)
#define SMKOT_8S				(0x02 << 2)
#define SMKOT_5S5				(0x03 << 2)
#define	CAPSENSITIVE_32			0x00		// 气压灵敏度 1/32
#define	CAPSENSITIVE_64			0x01		// 1/64
#define	CAPSENSITIVE_128		0x02		// 1/128
#define	CAPSENSITIVE_256		0x03		// (1~16)/256
//======= TRISA define============
#define PB1_SMT_37				0x00
#define PB1_SMT_24				0x80
#define UARTMUX_PB12			0x00	//PB2:TX  PB1:RX or RTX
#define UARTMUX_PB34			0x40	//PB4:TX  PB3:RX or RTX
//======= PBPU define============
#define PB7OUT_PU_EN			0x80
#define PB7OUT_PU_DIS			0x00
#define PB7OUT_PD_EN			0x01
#define PB7OUT_PD_DIS			0x00
//======= T0CON define============
#define BUZZER_EN				0x80
#define BUZZER_DIS				0x00
#define	T0CK_CPU				(0x00 << 5)
#define	T0CK_T0CKI_PB0			(0x01 << 5)
#define	T0CK_OSC33K				(0x02 << 5)
#define	T0CK_33HZ				(0x03 << 5)
#define T0SE_FALLEDGE			0x10
#define T0SE_RISEEDGE			0x00
#define PSA_EN					0x00
#define PSA_DIS					0x08
#define T0CKPS_DIV2				0x00
#define T0CKPS_DIV4				0x01
#define T0CKPS_DIV8				0x02
#define T0CKPS_DIV16			0x03
#define T0CKPS_DIV32			0x04
#define T0CKPS_DIV64			0x05
#define T0CKPS_DIV128			0x06
#define T0CKPS_DIV256			0x07
//======= T1CON0 define============
#define T1CK_T1CKI_PB5			(0x00 << 6)
#define T1CK_33HZ				(0x01 << 6)
#define T1CK_33K				(0x02 << 6)
#define T1CK_FCPU				(0x03 << 6)
#define T1CKPS_DIV1				(0x00 << 4)
#define T1CKPS_DIV4				(0x01 << 4)
#define T1CKPS_DIV8				(0x02 << 4)
#define T1CKPS_DIV16			(0x03 << 4)
#define T1SE_FALLEDGE			0x08
#define T1SE_RISEEDGE			0x00
#define T1SYNC_DIS				0x04
#define T1SYNC_EN				0x00
#define TM1CS_T1CK				0x02
#define TM1CS_FSYS				0x00
#define TM1_ON					0x01
#define TM1_OFF					0x00
//======= T1CON1 define============
#define INT0MAP_PA0				(0x00 << 4)
#define INT0MAP_PA1				(0x02 << 4)
#define INT0MAP_PA2				(0x04 << 4)
#define INT0MAP_PA3				(0x06 << 4)
#define INT0MAP_PA4				(0x08 << 4)
#define INT0MAP_PB0				(0x01 << 4)
#define INT0MAP_PB1				(0x03 << 4)
#define INT0MAP_PB2				(0x05 << 4)
#define INT0MAP_PB3				(0x07 << 4)
#define INT0MAP_PB4				(0x09 << 4)
#define INT0MAP_PB5				(0x0B << 4)
#define INT0MAP_PB6				(0x0D << 4)
#define INT0EDGE_FALL			0x08
#define INT0EDGE_RISE			0x00
#define T1OS_1PULSE				0x04
#define T1OS_CONTI				0x00
#define T1IF_PWM				0x02
#define T1IF_TIMER				0x00
#define T1MOD_PWM				0X01
#define	T1MOD_TIMER				0x00
//======= OSCCON define============
#define FINTOSC_1				(7 << 5)
#define FINTOSC_2				(6 << 5)
#define FINTOSC_4				(5 << 5)
#define FINTOSC_8				(4 << 5)
#define FINTOSC_16				(2 << 5)
#define CKOE_EN					0x10
#define CKOE_DIS				0x00
#define CKOE_EN					0x10
#define CKOE_DIS				0x00
#define OSC_HIGH				0x01
#define OSC_LOW					0x00

//======= PCON define============
#define WDT_EN					0x80
#define WDT_DIS					0x00
#define IIRST_IF				0x40
#define PDRV_SYSNC_EN			0X20	//PB6同步PB7的控制输出，PB6 = ~PB7
#define PDRV_SYSNC_DIS			0X00	
#define AFECLK_EN				0X10
#define AFECLK_DIS 				0X00
#define UARTCLK_EN				0X08
#define UARTCLK_DIS				0X00
#define PWMCLK_EN				0X04
#define PWMCLK_DIS				0X00
#define TM1CLK_EN				0X02
#define TM1CLK_DIS				0X00
#define TM0CLK_EN				0X01
#define TM0CLK_DIS				0X00
//======= PWMCON0 define============
#define AFE_CTRL_PMOS_EN		0X00
#define AFE_CTRL_PMOS_DIS		0X80
#define PWM0SP_REVERSE			0x10   // 反向输出
#define PWM0SP_DIRECT			0x00   // 同向输出
#define PWM0_OUTPUT_EN          0x01   
#define PWM0_OUTPUT_DIS         0x00 
//======= UARTCON define============
#define UART_PORT_EN			0x80
#define UART_PORT_DIS			0x00
#define UART_MODE9_EN			0x40
#define UART_MODE9_DIS			0x00
#define UART_HALFDUPLEX_EN		0x20
#define UART_HALFDUPLEX_DIS		0x00
#define UART_TX_EN				0x10
#define UART_TX_DIS				0x00
#define UART_BRG_DIV64			0x00
#define UART_BRG_DIV16			0x04
#define UART_BRG_DIV4			0x08
#define UART_BRG_DIV2			0x0C
#define UART_9BIT				0x02
#define UART_8BIT				0x00
#define UART_BUSY				0x01
#define UART_IDLE				0x00
//======= ADCON define============
#define ADCMOD_DUAL_FOLLOW		0x40
#define ADCMOD_CADC_FOLLOW		0x80
#define ADCMOD_NONE_FOLLOW		0xC0
#define VDAC1_SEL_VOUT			0x00
#define VDAC1_SEL_VBAT			0x10
#define VDAC1_SEL_VIN			0x20
// #define ADCSP_200US				0x08		//can't used
#define ADCSP_15MS				0x00
#define ADCMUX_V1C1				0x00
#define ADCMUX_V0C0				0x02
#define ADCMUX_V1C0				0x04
#define ADCMUX_C1C0				0x06
#define ADC_GO					0x01
//======= SMCR define============
#define SLEEPMOD_IDLE			(0x01 << 1)
#define SLEEPMOD_PWSAVE			(0x03 << 1)
#define SLEEPMOD_DEEPWSAVE		(0x05 << 1)
#define SLEEPMOD_PWOFF			(0x07 << 1)
//======= PIR0 define============
#define INTF_INT0				0x10
#define INTF_TM1				0x04
#define INTF_PBCHANGE		    0x02
#define INTF_TM0				0x01
//======= PIE0 define============
#define INTE_GIE				0x80
#define INTE_INT0				0x10
#define INTE_TM1				0x04
#define INTE_PBCHANGE		    0x02
#define INTE_TM0				0x01
//======= AFEIE0/AFEIF0 define============
#define AFE_SHORTCIRCUR			0x80
#define AFE_OVERCURRENT			0x40
#define AFE_UNDERVOLTAGE		0x20
#define AFE_OVERTEMP			0x08
#define AFE_SMKTIMEOUT			0x04
#define AFE_SMKSTOP				0x02
#define AFE_CAPSTART			0x01
//======= AFEIE1/AFEIF1 define============
#define AFE_KEY					0x40
#define AFE_CIGMOVE				0x20
#define AFE_CIGIN				0x10
#define AFE_CHGIN				0x08
#define AFE_CHGFULL				0x04
#define AFE_CHGOUT				0x01
//======= AFEIE2/AFEIF2 define============
#define AFE_CIG2S				0x80
#define AFE_KEY2S				0x40
#define AFE_SMK2S				0x20
#define AFE_CAD					0x10
#define AFE_VAD					0x08
#define AFE_UARTRX				0x04
#define AFE_UARTTX				0x02
//======= AFECTRL define============
#define LOCK_SMK_EN				0x20
#define LOCK_SMK_DIS			0x00
#define LOCK_CIG_EN				0x10
#define LOCK_CIG_DIS			0x00
#define LOCK_KEY_EN				0x08
#define LOCK_KEY_DIS			0x00
#define SMKING					0x04
#define NON_SMK					0x00
#define CHG_FULL				0x02
#define CHG_NOTFULL				0x00
#define CHGING					0x01
#define CHG_NOTCHG				0x00
//======= AFECTRL1 define============
#define SMK_OT_EN				0x80
#define SMK_OT_DIS				0x00
#define SMK_OTMOD_SW			0x40
#define SMK_OTMOD_HW			0x40
#define CIG_IN					0x08
#define CIG_OUT					0x00


#endif
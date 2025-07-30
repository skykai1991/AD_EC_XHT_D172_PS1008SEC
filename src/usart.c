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
#include <stdio.h>
#include <string.h>
#include "commdef.h"
#include "usart.h"
#include "charge.h"
#include "display_sentence.h"
#include "PS1008_DEF.h"
#include "PS1008_Core.h"
#define UART_HARDWARE
// #define UART_SOFTWARE

#ifdef _DEBUG_ONLINE_
u16 R_Uart_Rx_Data;
bit b_Uart_StartFlag;
bit b_UartRecevirFinish;
u8  R_Uart_RX_Count;
u8 R_UART_TimeOut;
#define BAUD_RATE 500000
#else
#define BAUD_RATE 2000000
#endif

#ifdef UART_HARDWARE
/* by Kennny Yeh 2024.9.4
设置波特率 分频比 实际波特率 误差百分比
9600	   16	  9615.384615	0.16%
14400	   16	  14492.75362	0.64%
19200	   4	  19230.76923	0.16%
38400	   2	  38461.53846	0.16%
57600	   2	  57553.95683	-0.08%
115200	   2	  115942.029	0.64%
128000	   2	  126984.127	-0.79%
230400	   2	  228571.4286	-0.79%
256000	   2	  258064.5161	0.81%
460800	   2	  470588.2353	2.12%
500000	   2	  500000	0.00%
921600	   2	  888888.8889	-3.55%
1000000	   2	  1000000	0.00%
2000000	   2	  2000000	0.00%

*/
void usart_init()
{
        UARTCLKEN = 1;
#ifdef _DEBUG_ONLINE_
	TX_DIR=1; 
	TX_PIN=1;
        RCIE = 1;
#else
	TX_DIR=0; 
	TX_PIN=1;
        RCIE = 0;
#endif
	SPEN =0;
	UART_MUX =0; //0：PB1(RX 和 RX_TX) ;PB2(TX)  1：PB3(RX 和 RX_TX) ;PB4(TX)
	UARTCON = UART_PORT_EN + UART_MODE9_DIS + UART_HALFDUPLEX_EN + UART_BRG_DIV2 + UART_8BIT;
	SPBRG=_XTAL_FREQ/2/BAUD_RATE;	//波特率

	AFECLKEN =1;// 使能IE 需要打开AFECLKEN
	RCIE =0;	//接收中断使能
	TXIE =0;	//发送中断使能	
}


void putch(unsigned char byte) 
{
	// while(!TXIF)continue;
        // TX_EN = 1;
	// TXREG = byte;
	TX_EN =1;
	TXREG = byte;
        u8 R_Timeout = 0xFF;
	while(!TXIF && R_Timeout--){asm("nop");}
        R_Timeout = 0xFF;
	while(BUSY && R_Timeout--){asm("nop");};
	TX_EN =0;

}


unsigned char getch() 
{
	while(!RCIF)continue;
	return RCREG;	
}

#endif

#ifdef UART_SOFTWARE
/***********************************
*函数名称：delay_bps
*函数功能：38400
***********************************/

void usart_init(void)
{
	TX_DIR=0; 
	TX_PIN=1;
}




void delay_bps1(void)
{
        unsigned char i;

        for(i=0;i<=5;i++) 
        {
                i++;
		NOP();NOP();NOP();NOP();NOP();
        }
        NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		
		
        CLRWDT();
}

void putch(unsigned char tmp)
{
    GIE  = 0;   //disable Interrupt
        // while(GIE == 1)
        // {
        //         GIE  = 0;
        // }
        
        USART_BUF = tmp;
        TX_PIN = 1;
        TX_PIN = 0; //START
        delay_bps1();
        TX_PIN = D0; //0
        delay_bps1();
        TX_PIN = D1;
        delay_bps1();
        TX_PIN = D2;
        delay_bps1();
        TX_PIN = D3;
        delay_bps1();
        TX_PIN = D4;
        delay_bps1();
        TX_PIN = D5;
        delay_bps1();
        TX_PIN = D6;
        delay_bps1();
        TX_PIN = D7;
        delay_bps1();
        TX_PIN = 1;     //stop
        delay_bps1();
        delay_bps1();
        
        GIE  = 1;   //enable Interrupt
}

#endif
// *******************************************************************************
// * Description    : Uart_Send
// * Function       : 发送数组
// * Input          : None.
// * Return         : 
// * Note           : None.
// *******************************************************************************/


void Uart_Send(unsigned char num, unsigned char siz, unsigned char *dat)
{
        putch(num);              // send command
        putch(siz);              // send length
        while(siz--)             // send data
	{
		putch(*dat);
	}
}

#ifdef _DEBUG_ONLINE_
// /*******************************************************************************
// * Description    : Uart_Send
// * Function       : 发送数组
// * Input          : None.
// * Return         : 
// * Note           : None.
// *******************************************************************************
void F_UART_ReceiverISR(void)
{       
        R_UART_TimeOut  = 5;
        if(!b_UartRecevirFinish)
        {
                R_Uart_Rx_Data <<= 8;
                R_Uart_Rx_Data |= RCREG;
                if(b_Uart_StartFlag)
                {
                        if(++R_Uart_RX_Count >= 2)
                        {
                                b_Uart_StartFlag = 0;  
                                R_Uart_RX_Count = 0;
                                b_UartRecevirFinish = 1;
                        }
                }
                else if(R_Uart_Rx_Data == 0xADAD)
                {
                        b_Uart_StartFlag =1;
                        R_Uart_RX_Count = 0;
                }
                else if(R_Uart_Rx_Data == 0xA5A5)
                {
                        R_Sleep_Off = D_8ms_5S; 
                }
        }
}
// /*******************************************************************************
// * Description    : F_DebugOnline
// * Function       : 接收数据解析处理
// * Input          : None.
// * Return         : 
// * Note           : None.
// *******************************************************************************
// DEBUG_ONLINE在线调试命令举例：
// 数据引导： 0xAD,0xAD    
// 数据头0xF5:0xF5  0x02    :表示要播放灯效02
// 数据头0xE7:0xE7  0x23    :表示要修改电量百分比 R_Battery_Percent = 0x23 = 35%
// 数据头0xDx0xD5  0x23    :表示要修改油量 R_OilRest = 0x523 = 1315秒
// 数据头0xC3:0xC3  0x41    :表示要修改输出功率 D_CP_SET = 0x41 = 65 即6.5W      
// 数据头0xBx:0xBC  0x1C    :表示要修改输出恒有效值 D_RMS_SET = 0xC1C = 3100 即3.1V
// 数据头0xAx:0xAC  0x1C    :表示要修改输出恒平均值 D_CV_SET = 0xC1C = 3100 即3.1V
// *******************************************************************************/
void F_DebugOnline(void)
{
        if(b_UartRecevirFinish)
        {
                // TX_DIR=0; 
                // TX_PIN=1;
                LOG_printf1("\r\n RxData:%x\r\n",R_Uart_Rx_Data);
                if((R_Uart_Rx_Data & 0xFF00) == 0xF500)
                {
                        F_PlayLight(R_Uart_Rx_Data & 0x000F);
                }
                else if((R_Uart_Rx_Data & 0xFF00) == 0xE700)
                {
                        if((R_Uart_Rx_Data & 0x00FF) <= Percent_Full)  R_Battery_Percent = R_Uart_Rx_Data & 0x00FF;
                }
                else if((R_Uart_Rx_Data & 0xF000) == 0xD000)
                {
                        if((R_Uart_Rx_Data & 0x0FFF) <= D_FullOil)  R_OilRest = R_Uart_Rx_Data & 0x0FFF;
                }
                else if((R_Uart_Rx_Data & 0xFF00) == 0xC300)
                {
#ifdef  _SMOKE_CTRL_CONST_POWER_
                        R_Temp16_0 = MTP_INFO_RD(0x0C);
                        CONSET = ((u32)(R_Uart_Rx_Data & 0x00FF) * R_Temp16_0 +5000)/10000;
#endif
                }
                else if((R_Uart_Rx_Data & 0xF000) == 0xB000)
                {
#ifdef  _SMOKE_CTRL_CONST_RMS_
			R_Temp16_0 = MTP_INFO_RD(0x0B);
                        R_Temp32 = (u32)(R_Uart_Rx_Data & 0x0FFF) * 1000 / R_Temp16_0 / 2;
                        R_Temp32 = R_Temp32 * R_Temp32 >>8;
                        CONSET = R_Temp32 + 2;
                        LOG_printf1("\r\n CONSET:%x\r\n",CONSET);
#endif
                }
                else if((R_Uart_Rx_Data & 0xF000) == 0xA000)
                {
#ifdef  _SMOKE_CTRL_CONST_VOLTAGE_
			R_Temp16_0 = MTP_INFO_RD(0x0B);
                        CONSET = ((u32)(R_Uart_Rx_Data & 0x0FFF)*1000 / R_Temp16_0) / 2;
#endif
                }

                b_UartRecevirFinish = 0;
                // TX_DIR=1; 
                // TX_PIN=1;
                // TX_EN  = 0;
        }
        if(R_UART_TimeOut)
        {
                R_UART_TimeOut--;
                if(!R_UART_TimeOut)
                {
                        b_UartRecevirFinish = 0;
                        b_Uart_StartFlag = 0;
                        b_Uart_StartFlag = 0;  
                        R_Uart_RX_Count = 0;
                        R_Uart_Rx_Data = 0;
                }
        }
}

#endif




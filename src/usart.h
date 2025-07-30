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

//UART_MUX	UART 的引脚映射
//0：PB1--RX和PB2--TX
//1：PB3--RX和PB4--TX

#include "common.h"
#include "PS1008_Core.h"

#ifndef _USART_H_
#define _USART_H_

volatile unsigned char	USART_BUF @0x21;	//RAM的地址
volatile bit D0			@ ((unsigned)&USART_BUF*8)+0;
volatile bit D1			@ ((unsigned)&USART_BUF*8)+1;
volatile bit D2			@ ((unsigned)&USART_BUF*8)+2;
volatile bit D3			@ ((unsigned)&USART_BUF*8)+3;
volatile bit D4			@ ((unsigned)&USART_BUF*8)+4;
volatile bit D5			@ ((unsigned)&USART_BUF*8)+5;
volatile bit D6			@ ((unsigned)&USART_BUF*8)+6;
volatile bit D7			@ ((unsigned)&USART_BUF*8)+7;

#define TX_DIR TRISB1
#define TX_PIN PB1


void usart_init(void);
void delay_bps1(void);
void putch(unsigned char tmp);
void Uart_Send(unsigned char num, unsigned char siz, unsigned char *dat);
#ifdef _DEBUG_ONLINE_
extern u16 R_Uart_Rx_Data;
extern bit b_Uart_StartFlag;
extern bit b_UartRecevirFinish;
extern u8  R_Uart_RX_Count;
void F_UART_ReceiverISR(void);
void F_DebugOnline(void);
#endif

#define LOG_printf0(fmt)                \
        {                               \
                F_DebugUart_Dis();      \
                usart_init();           \
                printf(fmt);            \
                F_DebugUart_En();       \
        }                     
#define LOG_printf1(fmt,a1)             \
        {                               \
                F_DebugUart_Dis();      \
                usart_init();           \
                printf(fmt,a1);         \
                F_DebugUart_En();       \
        }                     
#define LOG_printf2(fmt,a1,a2)          \
        {                               \
                F_DebugUart_Dis();      \
                usart_init();           \
                printf(fmt,a1,a2);      \
                F_DebugUart_En();       \
        }                     
#define LOG_printf3(fmt,a1,a2,a3)       \
        {                               \
                F_DebugUart_Dis();      \
                usart_init();           \
                printf(fmt,a1,a2,a3);   \
                F_DebugUart_En();       \
        }                     
    

#endif

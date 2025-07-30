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
#ifndef __RGB_LED_H__
#define __RGB_LED_H__

#include "PS1008.h"
#include "common.h"
#include <stdio.h>
#include "PS1008_DEF.h"
#include "HardwareDef.h"
#define PIN_LED PB4
#define _BREATH_FUNCTION_
#define LED_B_ON           PIN_LED = 0;
#define LED_B_OFF          PIN_LED = 1;


extern u8 R_color;
extern u8 R_Ontime_Reload;
extern u8 R_Offtime_Reload;
extern u8 R_Cycle;
extern u8 R_Ontime;
extern u8 R_Offtime;
extern u8 R_Breath_Level;

//==================功能说明=======================
// 此rgb_led.c & .h是实现RBG三色灯的闪烁程序；
// 调用LED_ON(color,ontime,offtime,cycle)表示接下来要显示的闪烁颜色，时间及循环次数；
// 10ms中断中调用F_RGB_Service_10ms()以控制实现LED的亮灭闪烁；

//==================================================
// F_RGB_Service_8ms
// This function must be run every 8ms；
//===================================================
void F_RGB_Service_8ms(void);

//==================================================
// name：LED_ON
// input:
//      color:  led_update- set as a new led on
//              light_red-red
//		        light_green-green
//		        light_blue-blue
//      ontime: 1-255 led on time,unit 10ms;
//      offtime: 1-255led off time,unit 10ms;
//      cycle: led show on-off times 
// void LED_ON(u8 color,u8 ontime,u8 offtime,u8 cycle);
// example1: LED 红灯，绿灯，蓝灯亮200ms+灭1000ms,循环5次
//      LED_ON(led_update + light_red + light_green + light_blue,20,100,5);
// example2: LED绿灯常亮（常亮则ON time,OFF time，cycle均设为0）
//      LED_ON(led_update + light_green,0,0,0);
// example3: LED红亮200ms后灭掉（off time不能为0，循环次数为1）
//      LED_ON(led_update + light_red,20,1,1);
// example3: LED红亮200ms后灭掉（off time不能为0，循环次数为1）
//      LED_ON(led_update + light_red,20,1,1);
// example4: LED红亮呼吸下降后亮蓝灯3S（led_breathdown为呼吸慢灭）
// LED_ON(led_update + light_blue + led_breathdown,300,1,1);
//===================================================
#define LED_ON(color,ontime,offtime,cycle) {R_color = color;R_Ontime_Reload = ontime;R_Offtime_Reload = offtime;R_Cycle = cycle;}
#define light_blue  0x01
#define light_all  0x01
#define led_update  0x10
#define led_breathup    0x20
#define led_breathdown    0x40
// #define led_last_status_ON    0x80
#define LED_OFF {R_color = 0;R_Ontime = 0;R_Offtime = 0;R_Cycle = 0;LED_B_OFF;T0IF = 0;T0IE = 0;}
#endif

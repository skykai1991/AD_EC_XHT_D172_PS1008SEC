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
#include "rgb_led.h"
u8 R_color = 0;
u8 R_Ontime_Reload = 0;
u8 R_Offtime_Reload = 0;
u8 R_Cycle = 0;
u8 R_Ontime = 0;
u8 R_Offtime = 0;
#ifdef _BREATH_FUNCTION_
u8 R_Breath_Level = 0;
#endif

void F_RGB_Service_8ms(void)
{
	if(R_color & led_update)
	{
		R_color &= (~led_update);
#ifdef _BREATH_FUNCTION_
		if(R_color & (led_breathup | led_breathdown))
		{
			// R_Breath_Level_cnt = 0;
			if(R_color & led_breathup)
				R_Breath_Level = 1;
			// else 
				// R_Breath_Level = 250;
			TMR0CLKEN = 1;
			T0CON = BUZZER_DIS + T0CK_CPU + T0SE_RISEEDGE + PSA_EN + T0CKPS_DIV256;
			PR0 = 250;		//8ms: _XTAL_FREQ/2/256/125
			TMR0 = 0;
			// T0IF = 0;
			T0IE = 0;
		}	
		else
#endif
		{
			R_Ontime = R_Ontime_Reload;
			R_Offtime =R_Offtime_Reload;
			if(R_Offtime)
			{
				LED_B_OFF;
			}
			else
			{
				LED_B_ON;
			}
		}
	}

#ifdef _BREATH_FUNCTION_
	if(R_color & (led_breathup | led_breathdown))
	{
			T0IE = 0;
			LED_B_ON;
			if(R_color & led_breathup) 
			{
				R_Breath_Level++;
				if(++R_Breath_Level >= 250)
				{
					R_color &= (~led_breathup);
					// LED_B_ON;
				}
				else
				{
					PR0 = R_Breath_Level;		//250=8ms: _XTAL_FREQ/2/256/125
					TMR0 = 0;
					T0IF = 0;
					T0IE = 1;
				}
			}
			else
			{
				R_Breath_Level--;
				if(--R_Breath_Level < 2)
				{
					R_color &= (~led_breathdown);
					LED_B_OFF;
					R_Cycle--;
					if(R_Cycle)
					{
						R_color |= led_breathup+led_breathdown;
					}
				}
				else
				{
					PR0 = R_Breath_Level;		//250=8ms: _XTAL_FREQ/2/256/125
					TMR0 = 0;
					T0IF = 0;
					T0IE = 1;
				}
				
			}
	}
#endif
	if(R_Offtime) 
	{
		R_Offtime--;
		if(!R_Offtime)
		{
			if(R_Ontime)
			{
				LED_B_ON;
			}
			else
			{
				R_Cycle--;
				if(R_Cycle)
				{
					R_Ontime = R_Ontime_Reload;
					R_Offtime =R_Offtime_Reload;
				}
			}
		}
	}
	else if(R_Ontime) 
	{
		R_Ontime--;
		if(!R_Ontime)
		{
			R_Cycle--;
			if(R_Cycle)
			{
				R_Ontime = R_Ontime_Reload;
				R_Offtime =R_Offtime_Reload;
				if(!R_Offtime)
				{
					LED_B_ON;
				}
				else
				{
					LED_B_OFF;
				}
			}
			else
			{
				LED_B_OFF;
			}				
		}
	}	
}



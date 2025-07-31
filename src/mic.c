/**********************************************************************************************
* Device      : PS1008
* Team        : ADUC FAE Team
* Description : 极简I/O扫描程序
* Version：
*       V0.0.1： Kenny.Yeh  2023.4.21
***********************************************************************************************/
#include "mic.h"
#include "display_sentence.h"
#include "usart.h"
#include "setting.h"
#include "key.h"
bit b_InputCurrent = 0;   //单次扫描当前状态
bit b_InputLast = 0;      //单次扫描上次状态
bit b_InputRecord = 0;    //消抖后，按键的状态记录
bit b_InputRecord_Last = 0;   //消抖后，上一次按键的状态记录
bit b_InputPress = 0;     //有效的按键按下
bit b_InputRelease = 0;   //有效的按键松开
bit b_Temp;
u8 R_DebounceCnt = 4; //消抖计数

void F_MICInput(void)
{
    b_InputLast = b_InputCurrent;
    b_InputCurrent = SMKINGS & (~PMOS_CTRL);
// #ifdef __DEBUG__
// GIE = 0;
// LOG_printf2("Cur %x,%x\r\n",PINA,R_InputCurrent);
// GIE = 1;
// #endif
    if(b_InputCurrent != b_InputLast)
    {
        R_DebounceCnt = 2;
    }
    else if(R_DebounceCnt)
    {
        R_DebounceCnt--;
        if(!R_DebounceCnt)
        {
            b_InputRecord = b_InputCurrent;
            b_Temp = b_InputRecord ^ b_InputRecord_Last;
            b_InputPress = b_Temp & b_InputRecord;
            b_InputRelease = b_Temp & b_InputRecord_Last;
            b_InputRecord_Last = b_InputRecord;
//--------------------------------------------------------------   
//按键扫描完毕，后面必须跟一着做按键事件的响应，只有一次机会置1；
//按键上升沿事件存于R_InputPress，下降沿事件存于R_InputRelease
//按键当前状态存于R_InputCurrent，按键消抖后状态存于R_InputRecord
//--------------------------------------------------------------   
// #ifdef __DEBUG__
// GIE = 0;
// LOG_printf2("key %x,%x\r\n",R_InputPress,R_InputRelease);
// GIE = 1;
// #endif
            if(b_InputPress &&(!bPerHeatFlag))
            {                      //MIC ON
			    b_SmokeFlag = 1;
#ifdef _RV_DET_SMKING_
                b_CheckRing_Flag = 0;
#endif
			    F_PlayLight(1);
#ifdef _DEBUG_EVENT_
LOG_printf0("MIC ON\n");
#endif
            }

    //-------------------------------------   
            if(b_InputRelease)
            {                      //mic off
                SOFTKEY =0;
                TMOMUX =0;
                if(b_SmokeFlag)
                {
                    b_SmokeFlag = 0;
                    F_PlayLight(2);
#ifdef _DEBUG_EVENT_
LOG_printf0("MIC OFF\n");
#endif
			    }
            }
  //--------------------------------------------------------------   
        }
    }
}
























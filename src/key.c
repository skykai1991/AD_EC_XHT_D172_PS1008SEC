/**********************************************************************************************
* Device      : PS1008
* Team        : ADUC FAE Team
* Description : 极简I/O扫描程序
* Version：
***********************************************************************************************/
#include "key.h"
#include "HardwareDef.h"
#include "common.h"
#include "display_sentence.h"
bit b_InputCurrentKEY = 0;   //单次扫描当前状态
bit b_InputLastKEY = 0;      //单次扫描上次状态
bit b_InputRecordKEY = 0;    //消抖后，按键的状态记录
bit b_InputRecord_LastKEY = 0;   //消抖后，上一次按键的状态记录
bit b_InputPressKEY = 0;     //有效的按键按下
bit b_InputReleaseKEY = 0;   //有效的按键松开
bit b_TempKEY;
u8 R_DebounceCntKEY = 4; //消抖计数

u8 R_InputKeyRepeatTime = 0; //按键重复时间
u8 R_InputKeyRepeatCount = 0; //按键重复计数
bit blockFlag;
/**
 * @brief 处理按键输入的函数
 * 
 * 此函数用于处理系统中的按键输入事件，根据不同的按键执行相应的操作。
 * 
 * @param void 无参数
 * @return void 无返回值
 */
void F_KEYInput(void)
{
    b_InputLastKEY = b_InputCurrentKEY;
    b_InputCurrentKEY = PIN_KEY;

    if(b_InputCurrentKEY != b_InputLastKEY)
    {
        R_DebounceCntKEY = 4;
    }
    else if(R_DebounceCntKEY)
    {
        R_DebounceCntKEY--;
        if(!R_DebounceCntKEY)
        {
            b_InputRecordKEY = b_InputCurrentKEY;
            b_TempKEY = b_InputRecordKEY ^ b_InputRecord_LastKEY;
            b_InputPressKEY = b_TempKEY & b_InputRecordKEY;
            b_InputReleaseKEY = b_TempKEY & b_InputRecord_LastKEY;
            b_InputRecord_LastKEY = b_InputRecordKEY;
//--------------------------------------------------------------   
//按键扫描完毕，后面必须跟一着做按键事件的响应，只有一次机会置1；
//按键上升沿事件存于R_InputPress，下降沿事件存于R_InputRelease
//按键当前状态存于R_InputCurrent，按键消抖后状态存于R_InputRecord
    //--------------------------------------------------------------   

            if(b_InputPressKEY) // 高电平有效
            { 
                     
            }

    //-------------------------------------   
            if(b_InputReleaseKEY) // 低电平有效
            {                      
                if(R_InputKeyRepeatTime)
                {
                   R_InputKeyRepeatCount++;
                }
                else
                {
                    R_InputKeyRepeatCount=1;
                }
               
                 R_InputKeyRepeatTime = D_8ms_500ms; 
                 if(R_InputKeyRepeatCount ==5)
                 {
                    blockFlag ^=1;    //开关机
                    F_PlayLight(10); 
                 }
                                  
                // if(bPerHeatFlag)
                // {
                //     F_StopSmoke();
			    //     F_PlayLight(2);
                // }
                // // else if(bChangePower)
                // // {
                // //     if(bCurrentPowerLevel<2) bCurrentPowerLevel++;
                // //     else bCurrentPowerLevel =0;

                // //     F_PlayLight(7);
                // // }
                // else if((blockFlag ==0)&& (R_InputKeyRepeatCount<5))
                // {
                //      F_MicON(); 
                // }
            }
  //--------------------------------------------------------------   
        }
    }
}

void F_PreHeat(void)
{
//     if((!R_InputKeyRepeatTime)&&(bPerHeatFlag==0) &&(blockFlag==0))
//     { 
// //     #ifdef __DEBUG__
// //             GIE = 0;
// //     printf("preheat\r\n");
// //     GIE = 1;
// // #endif 
//         if((R_InputKeyRepeatCount ==2) && ((R_InputRecord & (1<<BIT_KEY))))
//         {
         
//             R_InputKeyRepeatCount =0;

//             bPerHeatFlag =1;
//             F_MicON();
//         }

//         if(R_InputKeyRepeatCount ==3)
//         {
//              R_InputKeyRepeatCount =0;
//             if(bCurrentPowerLevel<2) bCurrentPowerLevel++;
//             else bCurrentPowerLevel =0;
//              F_PlayLight(7);
//         }
//     }

    // if(bPerHeatFlag && (!b_LightPlay_Flag))
    // {
    //      F_PlayLight(5);
    // }
}
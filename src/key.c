/**********************************************************************************************
* Device      : PS1008
* Team        : ADUC FAE Team
* Description : 极简I/O扫描程序
* Version：
***********************************************************************************************/
#include "smoke.h"
#include "key.h"
#include "HardwareDef.h"
#include "common.h"
#include "display_sentence.h"
#include "setting.h"
#include "PS1008_Core.h"
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
u16 R_PreHeatTime = 0; //按键重复延时
bit blockFlag;
bit bPerHeatFlag;
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
                R_Sleep_Off = D_8ms_600ms; 
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
                            
                if(bPerHeatFlag)
                {
                    bPerHeatFlag =0;
                    SOFTKEY =0;
                    F_PlayLight(13);
                }
            }
  //--------------------------------------------------------------   
        }
    }

    F_ChangeMode();
    F_PreHeat();

}

void F_ChangeMode(void)
{
    if((!R_InputKeyRepeatTime)&&(R_InputKeyRepeatCount ==3)&&(blockFlag==0))  // 调节挡位
    { 
       R_InputKeyRepeatCount =0;
       R_Mode++;
       if(R_Mode >3) R_Mode =1;
       F_PlayLight(12);  // 显示挡位

       // 调节输出电压
       	R_Temp16_0 = MTP_INFO_RD(0x0B);
       if(R_Mode==1)  CONSET = ((u32)D_CV_SET_1 / R_Temp16_0) / 2;
       else if(R_Mode ==2) CONSET = ((u32)D_CV_SET_2 / R_Temp16_0) / 2;
       else if(R_Mode ==3) CONSET = ((u32)D_CV_SET_3 / R_Temp16_0) / 2;
    }
}


void F_PreHeat(void)
{
    if((!R_InputKeyRepeatTime)&&(bPerHeatFlag==0) &&(blockFlag==0))
    { 
        if(R_InputKeyRepeatCount ==2)
        {
            R_InputKeyRepeatCount =0;
            //吸烟前检测
  	#ifdef _BOMB_INOUT_DETECT_
				if(b_Bomb_Online == 0)		//吸烟前开路
				{
					F_PlayLight(9);		//开路灯效
                    PWMCLKEN =1;
					PMOS_CTRL = 1;
					R_ErrFlag.OPEN = 1;
					return;
				}
				else
				{
					R_ErrFlag.OPEN = 0;
					if(R_ErrFlag.ErrFlag == 0 )
					{
                        PWMCLKEN =1;
						PMOS_CTRL = 0;
					}
				}
	#endif
				if(R_ErrFlag.LB)		//低电
				{
					F_PlayLight(4);
					return;
				}
				else if (R_ErrFlag.HZ || R_ErrFlag.LZ)		//高阻或低阻
				{
                    PWMCLKEN =1;
					PMOS_CTRL = 0;
					R_ErrFlag.HZ = 0;
					R_ErrFlag.LZ = 0;
				}
             //-------------------
   
            bPerHeatFlag =1;
            SOFTKEY =1;
            R_PreHeatTime = D_8ms_6S;
            R_Temp16_0 = MTP_INFO_RD(0x0B);
            CONSET = ((u32)D_CV_SET_PRE / R_Temp16_0) / 2;
            F_PlayLight(11);  // 预热显示

        }
    }

    if(bPerHeatFlag)
    {
        if(R_PreHeatTime)
        {
            R_PreHeatTime--;
            if(!R_PreHeatTime)
            {
                bPerHeatFlag =0;
                SOFTKEY =0;
                F_PlayLight(13);
            }
        }
    }
}
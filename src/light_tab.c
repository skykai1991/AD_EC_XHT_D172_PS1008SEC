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
#include "display_sentence.h"

// ===========灯效定义===========
const u8 Light0[]={    //上电  LED亮2S，数码管亮30秒，方便客户测试全屏显示电流。
    M_SHOW_NUM_LED(ICON_ALL,0x4,88,led_update+light_blue,2000,0,1,2000),
    DISPLAY_END
    };
const u8 Light1[]={    //吸烟
    M_SHOW_NUM_LED(ICON_PER+ICON_CY3+ICON_CY4,OIL_BY_REG,NUM_BY_REG,led_update+light_blue+led_breathup,0,0,1,0),
    M_LOOP_START(10),
    M_FLASHSET(ICON_PER+ICON_CY1,200),
    M_FLASHSET(ICON_PER+ICON_CY2,200),
    M_FLASHSET(ICON_PER+ICON_CY3,200),
    M_FLASHSET(ICON_PER+ICON_CY4,200),
    M_FLASHSET(ICON_PER+ICON_CY5,200),
    M_FLASHSET(ICON_PER,200),
    M_LOOP_END,
    // M_FLASHSET(ICON_PER+ICON_CY2+ICON_CY3+ICON_CY4+ICON_CY5,200),
    // M_FLASHSET(ICON_PER+ICON_CYCLE,200),
    // M_FLASHSET(ICON_PER+ICON_CY2+ICON_CY3+ICON_CY4+ICON_CY5,200),
    // M_FLASHSET(ICON_PER+ICON_CY3+ICON_CY4,200),
    // M_FLASHSET(ICON_PER,200),
    M_SHOW_NUM_LED(ICON_PER+ICON_CYCLE,OIL_BY_REG,NUM_BY_REG,led_update+light_blue+led_breathdown,0,0,1,1000),

    DISPLAY_END
    };
const u8 Light2[]={    //吸停
    M_SHOW_NUM_LED(ICON_PER+ICON_CYCLE,OIL_BY_REG,NUM_BY_REG,led_update+light_blue+led_breathdown,0,0,1,2000),
    DISPLAY_END
    };
const u8 Light3[]={    //过吸
    M_SHOW_NUM_LED(ICON_PER+ICON_CYCLE,OIL_BY_REG,NUM_BY_REG,led_update+light_blue,250,250,2,3000),
    DISPLAY_END
    };
const u8 Light4[]={    //欠压
    M_SHOW_NUM_LED(0,OIL_BY_REG,NUM_OFF,led_update+light_blue,200,200,10,200),
    M_SHOW_NUM(ICON_PER+ICON_CYCLE,OIL_BY_REG,0,200),
    M_LOOP_START(9),
    M_SHOW_NUM(0,OIL_BY_REG,NUM_OFF,200),
    M_SHOW_NUM(ICON_PER+ICON_CYCLE,OIL_BY_REG,0,200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light5[]={    //短路
    M_SHOW_NUM_LED(ICON_PER+ICON_CYCLE,OIL_BY_REG,NUM_BY_REG,led_update+light_blue,1000,0,2,2000),
    DISPLAY_END
     };
const u8 Light6[]={    //充电中
    M_SHOW_NUM_LED(ICON_PER+ICON_FLA,0,NUM_BY_REG,led_update+light_blue+led_breathup+led_breathdown,0,0,5,500),
    M_FLASHSET(ICON_PER,500),
    M_LOOP_START(9),
    M_FLASHSET(ICON_PER+ICON_FLA,500),
    M_FLASHSET(ICON_PER,500),
    M_LOOP_END,
    DISPLAY_END
    };

const u8 Light7[]={    //充电解除
    M_SHOW_NUM(ICON_PER,0,NUM_BY_REG,3000),
    DISPLAY_END
    };
const u8 Light8[]={    //充满
    M_SHOW_NUM(ICON_PER,0,NUM_BY_REG,60000),
    DISPLAY_END
    };
const u8 Light9[]={    
    M_SHOW_NUM_LED(ICON_PER+ICON_CYCLE,OIL_BY_REG,NUM_BY_REG,led_update+light_blue,1000,0,3,3000),
    DISPLAY_END
    };
// const u8 Light10[]={    // 档位切换 吸烟超时 卡键   =同开关机 
//     M_LOOP_START(3),
//     M_SEGTUBE_SCREENOFF(250),
//     M_SHOW_NUM_LED(NUM_BY_REG,NUM_BY_REG,led_update+light_blue,250,0,1,250),
//     M_LOOP_END,
//     DISPLAY_END
//      };

// ===========灯效总表===========
const u8* LightTab[10]={Light0,Light1,Light2,Light3,Light4,Light5,Light6,Light7,Light8,Light9};


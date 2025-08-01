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
const u8 Light0[]={    //上电  
    M_NIXTETUBE_FULLSCREEN(1000),
    DISPLAY_END
    };
const u8 Light1[]={    //吸烟
    M_SHOW_NUM(ICON_Bat+ICON_PCT,NUM_BY_Bat,10000),
    DISPLAY_END
    };
const u8 Light2[]={    //吸停
    M_SHOW_NUM(ICON_Bat+ICON_PCT,NUM_BY_Bat,4000),
    M_SHOW_NUM(0,NUM_BY_Mode,4000),
    M_SHOW_NUM(ICON_Oil+ICON_PCT,NUM_BY_Oil,4000),
    DISPLAY_END
    };
const u8 Light3[]={    //过吸
    M_LOOP_START(6),
    M_SEGTUBE_SCREENOFF(200),
    M_NIXTETUBE_FULLSCREEN(200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light4[]={    //欠压
    M_LOOP_START(8),
    M_SHOW_NUM(         ICON_PCT,NUM_BY_Bat,200),
    M_SHOW_NUM(ICON_Bat+ICON_PCT,NUM_BY_Bat,200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light5[]={    //短路
    M_LOOP_START(10),
    M_SEGTUBE_SCREENOFF(200),
    M_NIXTETUBE_FULLSCREEN(200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light6[]={    //充电中
    M_SHOW_NUM(ICON_Bat+ICON_PCT,NUM_BY_Bat,10000),
    DISPLAY_END
    };

const u8 Light7[]={    //充电解除
    M_LOOP_START(3),
    M_SEGTUBE_SCREENOFF(200),
    M_NIXTETUBE_FULLSCREEN(200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light8[]={    //充满
    M_SEGTUBE_SCREENOFF(10),
    DISPLAY_END
    };
const u8 Light9[]={     //开路
    M_LOOP_START(8),
    M_SEGTUBE_SCREENOFF(200),
    M_NIXTETUBE_FULLSCREEN(200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light10[]={    // 开关机 
    M_LOOP_START(2),
    M_SEGTUBE_SCREENOFF(200),
    M_NIXTETUBE_FULLSCREEN(200),
    M_LOOP_END,
    DISPLAY_END
    };
const u8 Light11[]={    // 预热开启
    M_SHOW_NUM(ICON_Oil,6,1000),
    M_SHOW_NUM(ICON_Oil,5,1000),
    M_SHOW_NUM(ICON_Oil,4,1000),
    M_SHOW_NUM(ICON_Oil,3,1000),
    M_SHOW_NUM(ICON_Oil,2,1000),
    M_SHOW_NUM(ICON_Oil,1,1100),
    DISPLAY_END
    };
 const u8 Light12[]={    // 档位切换 
    M_SHOW_NUM(0,NUM_BY_Mode,4000),
    DISPLAY_END
    };   

 const u8 Light13[]={    // 档位切换 
    M_SHOW_NUM(ICON_Bat+ICON_PCT,NUM_BY_Bat,2000), // 预热结束
    DISPLAY_END
    };  

// ===========灯效总表===========
const u8* LightTab[14]={Light0,Light1,Light2,Light3,Light4,Light5,Light6,Light7,Light8,Light9,Light10,Light11,Light12,Light13};


#ifndef __PS1008CORE_H__
#define __MYLIB_H__


#define UVL_3_3V 0
#define UVL_3_5V 1
#define UVL_3_0V 2
#define UVL_2_8V 3

#define CHRC_EN 1     //充电复充使能
#define CHRC_DIS 0    //充电复充禁止

#define CHRC_350mA 0 //充电电流350mA 
#define CHRC_500mA 1 //充电电流500mA
#define CHRC_800mA 2 //充电电流800mA
#define CHRC_600mA 3 //充电电流600mA
/*
函数：F_UVLO_SEL
功能：欠压挡位选择
参数范围：uvl  0~3
返回值：1---修改成功
       0---参数范围错误
*/
unsigned char F_UVP_VOLT_Setting(unsigned char uvl);

/*
函数：F_CHRC_580mA
功能：充电电流调节为580mA 
*/
void F_CHRC_580mA(void);


/*
函数：F_DEBUG_UART_ON
功能：UART调试模式使能
*/
void F_DebugUart_En(void);

/*
函数：F_DEBUG_UART_OFF
功能：UART调试模式关闭
*/
void F_DebugUart_Dis(void);

/*
函数：MTP_INFO_RD
功能：读取info中参数
参数：
    0x0A:  KVBAT
    0x0B:  KVOUT
    0x0C:  10W的 CONSET
    0x0D:  KCOUT
返回值：对应参数
*/
unsigned short MTP_INFO_RD(unsigned char addr);

/*
函数：Recharge
功能：充电: 是否开启复充功能
参数范围： mode  0---禁止复充 1---开启复充
返回值：1---修改成功
       0---参数范围错误
*/
unsigned char  Recharge(char mode);

/**
 * @brief 设置充电电流
 * @param mode 充电电流模式
 *             0x00: 350mA
 *             0x01: 500mA
 *             0x02: 800mA
 *             0x03: 600mA
 * return 1---修改成功  0---参数范围错误
 */
unsigned char Charge_Cur_Select(char mode);
#endif 
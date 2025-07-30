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
//************************************************************************************
//#Project  :PS1008A1
//#Version  :v0
//#DATE     :2024/12/25
//-------------------------change list------------------------------------------------
//====================================================================================
//--Version.----------------Content-----------------------------------------------------------Who---


//====================================================================================


#ifndef	__PS1008_H

#define	__PS1008_H


#define _XTAL_FREQ (16000000L)
#pragma intrinsic(_delay)
extern __nonreentrant void _delay(unsigned long);

#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/(4000000L))))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))


/* C access to assembler insructions */
#define CLRWDT()        asm(" clrwdt")
#define NOP()           asm(" nop")
#define RESET()         asm(" reset")
#define SLEEP()         asm(" sleep")

/* common definitions */
#define	___mkstr1(x)	#x
#define	___mkstr(x)	___mkstr1(x)

#define	__CONFIG(x)	asm("\tpsect config,class=CONFIG,delta=2");\
			asm("\tdw "___mkstr(x));


#define SLEEP_PWIDLE()      SMCR = 0X01; SLEEP();NOP()
#define SLEEP_PWSAVE()      SMCR = 0X03; SLEEP();NOP()
#define SLEEP_PWDEEP()      SMCR = 0X05; SLEEP();NOP()
#define SLEEP_PWOFF()       SMCR = 0X07; SLEEP();NOP()


static volatile unsigned char	INDF                    @0x00;
static volatile unsigned char	TMR0                    @0x01;
static volatile unsigned char	PCL                     @0x02;
static volatile unsigned char	STATUS                  @0x03;
/*Definitions for STATUS register*/
static volatile bit	 RP1                          @((unsigned)&STATUS*8)+6;
static volatile bit	 RP0                          @((unsigned)&STATUS*8)+5;
static volatile bit	 TO                           @((unsigned)&STATUS*8)+4;
static volatile bit	 PD                           @((unsigned)&STATUS*8)+3;
static volatile bit	 Z                            @((unsigned)&STATUS*8)+2;
static volatile bit	 DC                           @((unsigned)&STATUS*8)+1;
static volatile bit	 C                            @((unsigned)&STATUS*8)+0;


static volatile unsigned char	FSR                     @0x04;
static volatile unsigned char	PORTA                   @0x05;
/*Definitions for PORTA register*/
static volatile bit	 PA4                       @((unsigned)&PORTA*8)+4;
static volatile bit	 PA3                       @((unsigned)&PORTA*8)+3;
static volatile bit	 PA2                       @((unsigned)&PORTA*8)+2;
static volatile bit	 PA1                       @((unsigned)&PORTA*8)+1;
static volatile bit	 PA0                       @((unsigned)&PORTA*8)+0;


static volatile unsigned char	PORTB                   @0x06;
/*Definitions for PORTB register*/
static volatile bit	 PB6                       @((unsigned)&PORTB*8)+6;
static volatile bit	 PB5                       @((unsigned)&PORTB*8)+5;
static volatile bit	 PB4                       @((unsigned)&PORTB*8)+4;
static volatile bit	 PB3                       @((unsigned)&PORTB*8)+3;
static volatile bit	 PB2                       @((unsigned)&PORTB*8)+2;
static volatile bit	 PB1                       @((unsigned)&PORTB*8)+1;
static volatile bit	 PB0                       @((unsigned)&PORTB*8)+0;



static volatile unsigned char	PCON                    @0x08;
/*Definitions for PCON register*/
static volatile bit	 WDTEN                        @((unsigned)&PCON*8)+7;
static volatile bit	 RSTF                         @((unsigned)&PCON*8)+6;
static volatile bit	 PDRV_SYNC                    @((unsigned)&PCON*8)+5;
static volatile bit	 AFECLKEN                     @((unsigned)&PCON*8)+4;
static volatile bit	 UARTCLKEN                    @((unsigned)&PCON*8)+3;
static volatile bit	 PWMCLKEN                     @((unsigned)&PCON*8)+2;
static volatile bit	 TMR1CLKEN                    @((unsigned)&PCON*8)+1;
static volatile bit	 TMR0CLKEN                    @((unsigned)&PCON*8)+0;


static volatile unsigned char	PR0                     @0x09;
static volatile unsigned char	PCLATH                  @0x0a;


static volatile unsigned char	T0CON                   @0x0b;
/*Definitions for T0CON register*/
static volatile bit	 T0OUT                        @((unsigned)&T0CON*8)+7;
static volatile bit	 T0CS1                        @((unsigned)&T0CON*8)+6;
static volatile bit	 T0CS0                        @((unsigned)&T0CON*8)+5;
static volatile bit	 T0SE                         @((unsigned)&T0CON*8)+4;
static volatile bit	 PSA                          @((unsigned)&T0CON*8)+3;
static volatile bit	 PS2                          @((unsigned)&T0CON*8)+2;
static volatile bit	 PS1                          @((unsigned)&T0CON*8)+1;
static volatile bit	 PS0                          @((unsigned)&T0CON*8)+0;


static volatile unsigned char	TMR1L                   @0x0c;
static volatile unsigned char	TMR1H                   @0x0d;
static volatile unsigned int	TMR1                    @0x0c;


static volatile unsigned char	PIE0                    @0x0e;
/*Definitions for PIE0 register*/
static volatile bit	 GIE                          @((unsigned)&PIE0*8)+7;
static volatile bit	 INT0IE                       @((unsigned)&PIE0*8)+4;
static volatile bit	 T1IE                         @((unsigned)&PIE0*8)+2;
static volatile bit	 PBIE                         @((unsigned)&PIE0*8)+1;
static volatile bit	 T0IE                         @((unsigned)&PIE0*8)+0;


static volatile unsigned char	PIR0                    @0x0f;
/*Definitions for PIR0 register*/
static volatile bit	 MAPEN                        @((unsigned)&PIR0*8)+7;
static volatile bit	 INT0IF                       @((unsigned)&PIR0*8)+4;
static volatile bit	 T1IF                         @((unsigned)&PIR0*8)+2;
static volatile bit	 PBIF                         @((unsigned)&PIR0*8)+1;
static volatile bit	 T0IF                         @((unsigned)&PIR0*8)+0;


static volatile unsigned char	PR1L                  @0x10;
static volatile unsigned char	PR1H                  @0x11;
static volatile unsigned int    PR1                   @0x10;

static volatile unsigned char	PWM1DUTY0L            @0x12;
static volatile unsigned char	PWM1DUTY0H            @0x13;
static volatile unsigned int    PWM1DUTY              @0x12;

static volatile unsigned char	VADCL                 @0x14;
static volatile unsigned char	VADCH                 @0x15;
static volatile unsigned int    VADC                  @0x14;

static volatile unsigned char	CADCL                 @0x16;
static volatile unsigned char	CADCH                 @0x17;
static volatile unsigned int    CADC                  @0x16;

static volatile unsigned char	ADCON                 @0x18;

/*Definitions for ADCON0 register*/
static volatile bit	 ADC_MODE1                    @((unsigned)&ADCON*8)+7;
static volatile bit	 ADC_MODE0                    @((unsigned)&ADCON*8)+6;
static volatile bit	 VADCIN_MUX1                  @((unsigned)&ADCON*8)+5;
static volatile bit	 VADCIN_MUX0                  @((unsigned)&ADCON*8)+4;
static volatile bit	 AD_FAST                      @((unsigned)&ADCON*8)+3;
static volatile bit	 ADC_MUX1                     @((unsigned)&ADCON*8)+2;
static volatile bit	 ADC_MUX0                     @((unsigned)&ADCON*8)+1;
static volatile bit	 GO                           @((unsigned)&ADCON*8)+0;

static volatile unsigned char	AFECTRL1            @0x19;
/*Definitions for AFECTRL1 register*/
static volatile bit	 STMOEN                       @((unsigned)&AFECTRL1*8)+7;
static volatile bit	 TMOMUX                       @((unsigned)&AFECTRL1*8)+6;
static volatile bit	 SOFTKEY                      @((unsigned)&AFECTRL1*8)+5;
static volatile bit	 CIGN                         @((unsigned)&AFECTRL1*8)+4;



static volatile unsigned char	T1CON0                @0x1b;
/*Definitions for T1CON0 register*/
static volatile bit	 T1CK1                        @((unsigned)&T1CON0*8)+7;
static volatile bit	 T1CK0                        @((unsigned)&T1CON0*8)+6;
static volatile bit	 T1CKPS1                      @((unsigned)&T1CON0*8)+5;
static volatile bit	 T1CKPS0                      @((unsigned)&T1CON0*8)+4;
static volatile bit	 T1SE                         @((unsigned)&T1CON0*8)+3;
static volatile bit	 T1SYNC                       @((unsigned)&T1CON0*8)+2;
static volatile bit	 TMR1CS0                      @((unsigned)&T1CON0*8)+1;
static volatile bit	 TMR1ON                       @((unsigned)&T1CON0*8)+0;


static volatile unsigned char	T1CON1                  @0x1c;
/*Definitions for T1CON1 register*/
static volatile bit	 INT0MAP2                     @((unsigned)&T1CON1*8)+7;
static volatile bit	 INT0MAP1                     @((unsigned)&T1CON1*8)+6;
static volatile bit	 INT0MAP0                     @((unsigned)&T1CON1*8)+5;
static volatile bit	 INT0PORT                     @((unsigned)&T1CON1*8)+4;
static volatile bit	 INT0EDGE                     @((unsigned)&T1CON1*8)+3;
static volatile bit	 T1OS                         @((unsigned)&T1CON1*8)+2;
static volatile bit	 T1IF_SEL                     @((unsigned)&T1CON1*8)+1;
static volatile bit	 T1M0                         @((unsigned)&T1CON1*8)+0;


static volatile unsigned char	PWMCON0                 @0x1d;
/*Definitions for PWMCON0 register*/
static volatile bit	 PWM0SP                       @((unsigned)&PWMCON0*8)+4;
static volatile bit	 PWM0OE                       @((unsigned)&PWMCON0*8)+0;
static volatile bit	 PMOS_CTRL                    @((unsigned)&PWMCON0*8)+7;


static volatile unsigned char	CONSET                  @0x1e;

static volatile unsigned char	TRISA                   @0x85;
/*Definitions for TRISA register*/
static volatile bit	 PB1SMTV                      @((unsigned)&TRISA*8)+7;
static volatile bit	 UART_MUX                     @((unsigned)&TRISA*8)+6;
static volatile bit	 TRISA4                       @((unsigned)&TRISA*8)+4;
static volatile bit	 TRISA3                       @((unsigned)&TRISA*8)+3;
static volatile bit	 TRISA2                       @((unsigned)&TRISA*8)+2;
static volatile bit	 TRISA1                       @((unsigned)&TRISA*8)+1;
static volatile bit	 TRISA0                       @((unsigned)&TRISA*8)+0;


static volatile unsigned char	TRISB                   @0x86;
/*Definitions for TRISB register*/
static volatile bit	 TRISB7                       @((unsigned)&TRISB*8)+7;
static volatile bit	 TRISB6                       @((unsigned)&TRISB*8)+6;
static volatile bit	 TRISB5                       @((unsigned)&TRISB*8)+5;
static volatile bit	 TRISB4                       @((unsigned)&TRISB*8)+4;
static volatile bit	 TRISB3                       @((unsigned)&TRISB*8)+3;
static volatile bit	 TRISB2                       @((unsigned)&TRISB*8)+2;
static volatile bit	 TRISB1                       @((unsigned)&TRISB*8)+1;
static volatile bit	 TRISB0                       @((unsigned)&TRISB*8)+0;


static volatile unsigned char	WUBCON                  @0x88;
/*Definitions for WUBCON register*/
static volatile bit	 WUB6                         @((unsigned)&WUBCON*8)+6;
static volatile bit	 WUB5                         @((unsigned)&WUBCON*8)+5;
static volatile bit	 WUB4                         @((unsigned)&WUBCON*8)+4;
static volatile bit	 WUB3                         @((unsigned)&WUBCON*8)+3;
static volatile bit	 WUB2                         @((unsigned)&WUBCON*8)+2;
static volatile bit	 WUB1                         @((unsigned)&WUBCON*8)+1;
static volatile bit	 WUB0                         @((unsigned)&WUBCON*8)+0;


static volatile unsigned char	OSCCON                  @0x89;
/*Definitions for OSCCON register*/
static volatile bit	 FINTOSC2                     @((unsigned)&OSCCON*8)+7;
static volatile bit	 FINTOSC1                     @((unsigned)&OSCCON*8)+6;
static volatile bit	 FINTOSC0                     @((unsigned)&OSCCON*8)+5;
static volatile bit	 CKOE                         @((unsigned)&OSCCON*8)+4;
static volatile bit	 OSCF                         @((unsigned)&OSCCON*8)+2;
static volatile bit	 OSCM                         @((unsigned)&OSCCON*8)+0;


static volatile unsigned char	AFEIF0                  @0x8c;
/*Definitions for AFEIF0 register*/
static volatile bit	 SCPIF                        @((unsigned)&AFEIF0*8)+7;
static volatile bit	 OCPIF                        @((unsigned)&AFEIF0*8)+6;
static volatile bit	 UVPIF                        @((unsigned)&AFEIF0*8)+5;
static volatile bit	 PWMIF                        @((unsigned)&AFEIF0*8)+4;
static volatile bit	 OTPIF                        @((unsigned)&AFEIF0*8)+3;
static volatile bit	 SMKTMOIF                     @((unsigned)&AFEIF0*8)+2;
static volatile bit	 SMKOVERIF                    @((unsigned)&AFEIF0*8)+1;
static volatile bit	 SMKSTARTIF                   @((unsigned)&AFEIF0*8)+0;


static volatile unsigned char	AFEIF1                  @0x8d;
/*Definitions for AFEIF1 register*/
static volatile bit	 KEYIF                        @((unsigned)&AFEIF1*8)+6;
static volatile bit	 CIGRMVIF                     @((unsigned)&AFEIF1*8)+5;
static volatile bit	 CIGINIF                      @((unsigned)&AFEIF1*8)+4;
static volatile bit	 CHGINIF                      @((unsigned)&AFEIF1*8)+3;
static volatile bit	 CHGFULLIF                    @((unsigned)&AFEIF1*8)+2;
static volatile bit	 PMOSIF                       @((unsigned)&AFEIF1*8)+1;
static volatile bit	 CHGRMVIF                     @((unsigned)&AFEIF1*8)+0;


static volatile unsigned char	AFEIF2                  @0x8e;
/*Definitions for AFEIF2 register*/
static volatile bit	 CIG2SIF                      @((unsigned)&AFEIF2*8)+7;
static volatile bit	 KEY2SIF                      @((unsigned)&AFEIF2*8)+6;
static volatile bit	 CAP2SIF                      @((unsigned)&AFEIF2*8)+5;
static volatile bit	 CADIF                        @((unsigned)&AFEIF2*8)+4;
static volatile bit	 VADIF                        @((unsigned)&AFEIF2*8)+3;
static volatile bit	 RCIF                         @((unsigned)&AFEIF2*8)+2;
static volatile bit	 TXIF                         @((unsigned)&AFEIF2*8)+1;



static volatile unsigned char	AFEIE0                  @0x8f;
/*Definitions for AFEIE0 register*/
static volatile bit	 SCPIE                        @((unsigned)&AFEIE0*8)+7;
static volatile bit	 OCPIE                        @((unsigned)&AFEIE0*8)+6;
static volatile bit	 UVPIE                        @((unsigned)&AFEIE0*8)+5;
static volatile bit	 PWMIE                        @((unsigned)&AFEIE0*8)+4;
static volatile bit	 OTPIE                        @((unsigned)&AFEIE0*8)+3;
static volatile bit	 SMKTMOIE                     @((unsigned)&AFEIE0*8)+2;
static volatile bit	 SMKOVERIE                    @((unsigned)&AFEIE0*8)+1;
static volatile bit	 CAPSTARTIE                   @((unsigned)&AFEIE0*8)+0;


static volatile unsigned char	AFEIE1                  @0x90;
/*Definitions for AFEIE1 register*/
static volatile bit	 KEYIE                        @((unsigned)&AFEIE1*8)+6;
static volatile bit	 CIGRMVIE                     @((unsigned)&AFEIE1*8)+5;
static volatile bit	 CIGINIE                      @((unsigned)&AFEIE1*8)+4;
static volatile bit	 CHGINIE                      @((unsigned)&AFEIE1*8)+3;
static volatile bit	 CHGFULLIE                    @((unsigned)&AFEIE1*8)+2;
static volatile bit	 PMOSIE                       @((unsigned)&AFEIE1*8)+1;
static volatile bit	 CHGRMVIE                     @((unsigned)&AFEIE1*8)+0;


static volatile unsigned char	AFEIE2                  @0x91;
/*Definitions for AFEIE2 register*/
static volatile bit	 CIG2SIE                       @((unsigned)&AFEIE2*8)+7;
static volatile bit	 KEY2SIE                       @((unsigned)&AFEIE2*8)+6;
static volatile bit	 CAP2SIE                       @((unsigned)&AFEIE2*8)+5;
static volatile bit	 CADIE                         @((unsigned)&AFEIE2*8)+4;
static volatile bit	 VADIE                         @((unsigned)&AFEIE2*8)+3;
static volatile bit	 RCIE                          @((unsigned)&AFEIE2*8)+2;
static volatile bit	 TXIE                          @((unsigned)&AFEIE2*8)+1;



static volatile unsigned char	AFECTRL               @0x92;
/*Definitions for AFESTATUS register*/
static volatile bit	 CPU_DISCHG                   @((unsigned)&AFECTRL*8)+7;
static volatile bit	 CPU_CTRL                     @((unsigned)&AFECTRL*8)+6;
static volatile bit	 SMKINGS                      @((unsigned)&AFECTRL*8)+2;
static volatile bit	 CHGFULLS                     @((unsigned)&AFECTRL*8)+1;
static volatile bit	 CHGENS                       @((unsigned)&AFECTRL*8)+0;



static volatile unsigned char	UARTCON                 @0x93;
/*Definitions for UARTCON  register*/
static volatile bit	 SPEN                         @((unsigned)&UARTCON *8)+7;
static volatile bit	 MODE9                        @((unsigned)&UARTCON *8)+6;
static volatile bit	 HALF_DUPLEX                  @((unsigned)&UARTCON *8)+5;
static volatile bit	 TX_EN                        @((unsigned)&UARTCON *8)+4;
static volatile bit	 BRGM                         @((unsigned)&UARTCON *8)+3;
static volatile bit	 BRGH                         @((unsigned)&UARTCON *8)+2;
static volatile bit	 TX9_RX9                      @((unsigned)&UARTCON *8)+1;
static volatile bit	 BUSY                         @((unsigned)&UARTCON *8)+0;


static volatile unsigned char	SPBRG                   @0x94;
static volatile unsigned char	RCREG                   @0x95;
static volatile unsigned char	TXREG                   @0x96;
static volatile unsigned char	PBPU                    @0x9e;
/*Definitions for PBPU register*/
static volatile bit	 CIGPUR                       @((unsigned)&PBPU*8)+7;
static volatile bit	 PUB6                         @((unsigned)&PBPU*8)+6;
static volatile bit	 PUB5                         @((unsigned)&PBPU*8)+5;
static volatile bit	 PUB4                         @((unsigned)&PBPU*8)+4;
static volatile bit	 PUB3                         @((unsigned)&PBPU*8)+3;
static volatile bit	 PUB2                         @((unsigned)&PBPU*8)+2;
static volatile bit	 PUB1                         @((unsigned)&PBPU*8)+1;
static volatile bit	 CIGPDR                       @((unsigned)&PBPU*8)+0;


static volatile unsigned char	SMCR                    @0x9f;

static volatile bit	 SM2                          @((unsigned)&SMCR*8)+3;
static volatile bit	 SM1                          @((unsigned)&SMCR*8)+2;
static volatile bit	 SM0                          @((unsigned)&SMCR*8)+1;
static volatile bit	 SE                           @((unsigned)&SMCR*8)+0;


static volatile unsigned char	LED_CTRL                    @0x9e;		//需要开MAPEN
/*Definitions for LED_CTRL register*/
static volatile bit	 CPU_LED_EN                   @((unsigned)&LED_CTRL*8)+5;


/* Address definitions for config word registers
// * (NOT TO BE USED WITH __CONFIG MACRO!) */
#define CONFIG1L	0x300000
#define CONFIG1H	0x300001
#define CONFIG2L	0x300002
#define CONFIG2H	0x300003
#define CONFIG3L	0x300004
#define CONFIG3H	0x300005
#define CONFIG4L	0x300006
#define CONFIG4H	0x300007
#define CONFIG5L	0x300008
#define CONFIG5H	0x300009
#define CONFIG6L	0x30000A
#define CONFIG6H	0x30000B
#define CONFIG7L	0x30000C
#define CONFIG7H	0x30000D


#endif


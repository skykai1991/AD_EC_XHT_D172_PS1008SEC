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
/*******************************************************************************
* Description : 通用宏定义
********************************************************************************/


#ifndef __COMMDEF_H__
#define __COMMDEF_H__

/********************************TYPEDEFS*************************************/
 
//常用数据类型定义
 
typedef signed   char   int8_t;     //!< Signed 8 bit integer
typedef unsigned char   uint8_t;    //!< Unsigned 8 bit integer
typedef volatile unsigned char vu8;  //!<volatile Unsigned 8 bit integer

typedef signed   short  int16_t;    //!< Signed 16 bit integer
typedef unsigned short  uint16_t;   //!< Unsigned 16 bit integer
typedef volatile unsigned short vu16; //!<volatile Unsigned 16 bit integer

typedef signed   long   int32_t;    //!< Signed 32 bit integer
typedef unsigned long   uint32_t;   //!< Unsigned 32 bit integer
typedef volatile unsigned long vu32; //!<volatile Unsigned 32 bit integer

typedef unsigned char   bool;     //!< Boolean data type

typedef volatile bit  vbit;

typedef unsigned char uchar;
typedef unsigned int  uint; 

typedef signed long         s32;
typedef signed short long   s24;
typedef signed short        s16;
typedef signed char         s8;
typedef unsigned long       u32;
typedef unsigned short long u24;
typedef unsigned short      u16;
typedef unsigned char       u8;

/********************************CONSTANTS************************************/

//常用的开关常量定义

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF	0
#endif

#ifndef RISING
#define RISING 1
#endif

#ifndef FALLING
#define FALLING 0
#endif




/*********************************MACROS**************************************/

//位操作相关的宏定义

#ifndef BV
#define BV(n)      (1 << (n))
#endif

#ifndef BF
#define BF(x,b,s)  (((x) & (b)) >> (s))
#endif

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif


/* takes a byte out of a uint32_t : var - uint32_t,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32( var, ByteNum ) \
          (uint8_t)((uint32_t)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32_t)((uint32_t)((Byte0) & 0x00FF) \
          + ((uint32_t)((Byte1) & 0x00FF) << 8) \
          + ((uint32_t)((Byte2) & 0x00FF) << 16) \
          + ((uint32_t)((Byte3) & 0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16_t)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)

#define HI_BYTE(x)   (((x)>>8)&0xFF)
#define LO_BYTE(x)   ((x)&0xFF)


#define BUILD_UINT8(hiByte, loByte) \
          ((uint8_t)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a) (((a) >> 4) & 0x0F)
#define LO_UINT8(a) ((a) & 0x0F)

/*********************************DebugExchage**************************************/
#define DEBUG

#ifdef DEBUG
    #define PRINTF printf
#else
    #define PRINTF
#endif

#endif /* COMDEF_H */
    
    
    
    
    
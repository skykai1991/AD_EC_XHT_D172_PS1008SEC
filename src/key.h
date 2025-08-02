#ifndef __KEY_H__
#define __KEY_H__
#include "commdef.h"
#include "PS1008.h"
// #define M_KEY_INT {b_InputRecord_LastKEY = b_InputCurrentKEY = 0;}

extern void F_KEYInput(void);
extern void F_ChangeMode(void);
extern void F_PreHeat(void);
extern void F_Switch(void);
// extern bit b_InputRecord_LastKEY;
// extern bit b_InputCurrentKEY;
extern bit blockFlag;
extern bit bPerHeatFlag;
extern  u8 R_InputKeyRepeatTime; 
#endif
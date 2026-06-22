#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"


float PID_PositionPidA(int16_t Ptn_Target, int16_t Ptn_Current);
float PID_PositionPidB(int16_t Ptn_Target, int16_t Ptn_Current);

#endif


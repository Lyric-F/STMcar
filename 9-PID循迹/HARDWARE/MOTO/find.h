#ifndef __FIND_H
#define __FIND_H

#include "stm32f10x.h"
//寻迹传感器从右到左以此O1 O2 O3 O4 
#define Find_O1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)	   //定义循迹模块的输入接口
#define Find_O2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define Find_O3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define Find_O4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)

void Find_IO_Init(void);

int Find(void);


#endif

#ifndef __TB6612_H
#define __TB6612_H

#include "stm32f10x.h"
#include "bsp_sys.h"

//硬件链接说明

//             PWMA ---- PB9
//             PWMB ---- PB8
//             INA2 ---- PB15
//             INA1 ---- PB14
//             INB1 ---- PB13
//             INB2 ---- PB12


#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

/* 带参宏，可以像内联函数一样使用 */
#define AIN2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define AIN1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)
					
#define BIN1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)
					
#define BIN2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)

void TB6612_Init(void);
void TB6612_PWM_Init(u32 arr, int psc);
void TB6612_PWM_Out(u16 moto_A, u16 moto_B);
void TB6612_GPIO_Config(void);
void Motor_A(u8 state);
void Motor_B(u8 state);
void Car_Go(void);					
void Car_Back(void);						
void Car_Left(void);
void Car_Right(void);
void Car_Stop(void);
void Motor_A_SetPWM(int16_t PWM);
void Motor_B_SetPWM(int16_t PWM);
void TB6612_Motor_SetPWM(int16_t PWMA,int16_t PWMB);//符号表示电机转动方向 3000表示占空比，占空比=3000/7200
					
#endif

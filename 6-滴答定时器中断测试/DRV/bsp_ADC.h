/*
********************************************************************************************************
文件名：bsp_ADC.c
功  能：ADC电压采样
备  注：
	硬件连接	
	    	STM32         TB6612
			PB0		----	BAT   电池电压采样 电阻分压1：10
			PB1		----	SYS	  系统电压采样 电阻分压1：1

淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/
#ifndef _BSP_ADC_H
#define _BSP_ADC_H

#include "stm32f10x.h"
#include "delay.h"

void ADC_Power_Init(void);
u16 Get_Adc(u8 ch) ;
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Get_BAT_ADC(void);
u16 Get_SYS_ADC(void);

#endif


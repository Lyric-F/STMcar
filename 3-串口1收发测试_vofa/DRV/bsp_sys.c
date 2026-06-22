/*
********************************************************************************************************
文件名：bsp_sys.c
功  能：初始化所有外设
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "bsp_sys.h"

void STM32_System_Init(void)
{	
	//STM32内部初始化
	NVIC_Config();         //中断配置配置初始化
	LED_GPIO_Init();    	 //LED初始化
	IIC_Init();						 //IIC硬件初始化
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,0,"B:    V , ",12);
	OLED_ShowString(80,0,"S:   V",12);
	ADC_Power_Init();      //ADC初始化
	USART1_Init(115200);	 //串口1初始化
	
	Delay_ms(100);          //等待初始化完成
}



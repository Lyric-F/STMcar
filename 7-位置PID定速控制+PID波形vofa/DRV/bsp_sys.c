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
/*
********************************************************************************************************
函数名称：void STM32_System_Init(void)
函数功能：系统初始化
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void STM32_System_Init(void)
{	
	//STM32内部初始化
	NVIC_Config();         //中断配置配置初始化
	LED_GPIO_Init();    	 //LED初始化
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	IIC_Init();						 //IIC硬件初始化
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,0,"B:    V , ",12);
	OLED_ShowString(80,0,"S:   V",12);
	OLED_ShowString(0,1,"B:   ,",12);
	OLED_ShowString(64,1,"A:   ",12);
	OLED_ShowString(0,2,"SET:    RPM",12);
	ADC_Power_Init();      //ADC初始化
	USART1_Init(115200);	 //串口1初始化
	
	TB6612_Init();  				//TB6612的初始化
	Encoder_Init_TIM2();
	Read_Encoder(2);
	Encoder_Init_TIM3();
	Read_Encoder(3);
	
	SysTick_Init();
	Delay_ms(100);          //等待初始化完成
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	Delay_ms(500); 
	
}



/*
********************************************************************************************************
文件名：bsp_NVIC.c
功  能：中断配置
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

/*
********************************************************************************************************
更新日志：
1.2017-2-6,编写uart和time中断


*********************************************************************************************************
*/

#include "bsp_nvic.h"

/*
********************************************************************************************************
函数名称：void NVIC_Config(void)
函数功能：配置各个中断的优先级
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void NVIC_Config(void)
{
	NVIC_TIM1_Config();
}





//配置timer1的中断配置
void NVIC_TIM1_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//------------------End of File----------------------------

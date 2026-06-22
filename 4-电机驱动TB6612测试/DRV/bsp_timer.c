/*
********************************************************************************************************
文件名：bsp_timer.c
功  能：
备  注：
			  	timer1 用于系统100ms定时功能
				timer2 用于左电机编码器计数
				timer4 用于右电机编码器计数

*********************************************************************************************************
*/


#include "bsp_timer.h"

/*
********************************************************************************************************
函数名称：void Timer1_Init(void)
函数功能：定时器1初始化 系统每10ms处理一次中断，更新数据，更新pwm等
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void Timer1_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 999;//自动重新装载寄存器周期的值澹ㄥ计数值澹)
	TIM_TimeBaseStructure.TIM_Prescaler = 719;//时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对外部时钟进行采样的时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //高级定时器1是用定时器功能配置这个才可以是正常的计数频率一开始的72mhz 值得注意的地方
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//参数初始化

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM1, ENABLE);//启动定时器 
}



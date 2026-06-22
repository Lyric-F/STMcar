/*
********************************************************************************************************
文件名：Encoder.c
功  能：配置编码器
备  注：
	硬件连接	STM32          TB6612的标识
				PA15 ------   B1A		A电机--TIM2
				PB3  ------   B1B
				PB4  ------   B2A		B电机--TIM3
				PB5  ------   B2B
		
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "Encoder.h"



/*
********************************************************************************************************
函数名称：void Encoder_Init_TIM2(void)
函数功能：定时器2初始化 ，使用编码器功能
硬件连接：//TB6612 A电机编码器计数
		//PA15----接 编码器A相 或者电机驱动的B1A标识
		//PB3 ----接 编码器B相 或者电机驱动的B1B标识
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void Encoder_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //禁用JTAG
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);

	TIM_Cmd(TIM2, ENABLE);   
}



/*
********************************************************************************************************
函数名称：void Encoder_Init_TIM3(void)
函数功能：定时器3初始化 ，使用编码器功能
硬件连接：	//TB6612 B电机编码器计数
			//PB4----接 编码器A相 或者电机驱动的B2A标识
			//PB5----接 编码器B相 或者电机驱动的B2B标识
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void Encoder_Init_TIM3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//TIM时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 , ENABLE); //这个就是重映射功能函数

	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 65535;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	TIM_Cmd(TIM3, ENABLE);  
	
	
}

/*
********************************************************************************************************
函数名称：int Read_Encoder(u8 TIMX)
函数功能：单位时间读取编码器计数,定时器不是从0开始计数，  这里读取定时器后都是会重新初始化定时器的计数器值为30000
硬件连接：	
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/

int16_t Read_Encoder(u8 TIMX)
{
    int16_t Encoder_TIM;    
   switch(TIMX)
	 {
		case 2:  Encoder_TIM=TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;
		case 3:  Encoder_TIM=TIM_GetCounter(TIM3); TIM_SetCounter(TIM3, 0); break;
		//case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=30000;break;	
		//case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=30000;break;
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}




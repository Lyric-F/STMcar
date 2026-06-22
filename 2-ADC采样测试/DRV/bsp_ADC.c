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

#include "bsp_adc.h"
/*
********************************************************************************************************
函数名称：void ADC_Power_Init(void)
函数功能：初始化ADC采样口
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void ADC_Power_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;	
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );					//GPIO外设时钟使能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;					//ADC端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;							//配置成模拟输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE );					//ADC1外设时钟使能
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 							//ADC连续转换
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//无ADC外部触发源
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//转换结果右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;					// 转换通道1个
	ADC_Init(ADC1, &ADC_InitStructure);										

	ADC_Cmd(ADC1, ENABLE);													//ADC启动
	ADC_ResetCalibration(ADC1);												//ADC复位
	while(ADC_GetResetCalibrationStatus(ADC1));								//ADC等待重启	
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);									//ADC软件转换模式
}
/*
********************************************************************************************************
函数名称：u16 Get_Adc(u8 ch) 
函数功能：初始化ADC采样口
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
u16 Get_Adc(u8 ch)   
{
  	//配置ADC的虚拟通道
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	 			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	return ADC_GetConversionValue(ADC1);	
}
/*
********************************************************************************************************
函数名称：u16 Get_Adc_Average(u8 ch,u8 times)
函数功能：转换结果
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
	}
	return temp_val/times;
}

/*
********************************************************************************************************
函数名称：u16 Get_BAT_ADC(void)
函数功能：电池电压采样
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
u16 Get_BAT_ADC(void)
{
	return Get_Adc(ADC_Channel_8);
}
/*
********************************************************************************************************
函数名称：u16 Get_SYS_ADC(void)
函数功能：系统电压采样
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
u16 Get_SYS_ADC(void)
{
	return Get_Adc(ADC_Channel_9);
}




#include "car.h"

u8 temp1=0;
u8 OLED_Timer1=0;//时间片，更新ADC
u8 OLED_Timer2=0;//时间片，更新速度

u8 OLED_ADC_Flag=0;
u8 OLED_Speed_Flag=0;

u16 ADC_BAT_Val,ADC_BAT_temp;
u16 ADC_SYS_Val,ADC_SYS_temp;

//Time1定时器1中断服务函数
//10ms定时
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM1, TIM_IT_Update) != RESET)   //时间到了
	{
		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);//清中断
		LED_Flash(50);//500ms闪烁一次
		
		temp1++;
		OLED_Timer1++;
		OLED_Timer2++;
		ADC_BAT_temp += Get_BAT_ADC();//ADC 采样 电池电压
		ADC_SYS_temp += Get_SYS_ADC();//aDC 采样 系统电压
		
		if(temp1>=10)//100ms
		{
			temp1=0;
			ADC_BAT_Val = ADC_BAT_temp/10;
			ADC_SYS_Val = ADC_SYS_temp/10;
			ADC_BAT_temp = 0;
			ADC_SYS_temp = 0;
		}
		
		if(OLED_Timer1 >= 100)//1S 更新一次ADC
		{
			OLED_Timer1=0;
			OLED_ADC_Flag = 1;
		}

		
		
		
		
	}
	
		
}




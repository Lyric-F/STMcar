/*
********************************************************************************************************
文件名：delay.c
功  能：延时函数us ms
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "car.h"

u8 temp1=0;
u8 OLED_Timer1=0;//时间片，更新ADC
u8 OLED_Timer2=0;//时间片，更新速度

u8 OLED_ADC_Flag=0; 			//显示ADC中断标志位
u8 OLED_Speed_Flag=0;			//显示速度标志位
u8 Encoder_Timer =0;

u16 ADC_BAT_Val,ADC_BAT_temp;
u16 ADC_SYS_Val,ADC_SYS_temp;

int Encoder_A,Encoder_B;  //编码器实际脉冲数
int Speed_A,Speed_B;		//电机实际转速

extern float Integral;
//uint16_t jsb = 1320;//11x30x4,电机的输出轴转一圈产生的脉冲数量。11是电机霍尔转动一圈的脉冲数量，30是减速比，4是四倍频
uint16_t jsb = 2112;//11x48x4,电机的输出轴转一圈产生的脉冲数量。11是电机霍尔转动一圈的脉冲数量，48是减速比，4是四倍频
//uint16_t jsb = 3960;//11x30x4,电机的输出轴转一圈产生的脉冲数量。11是电机霍尔转动一圈的脉冲数量，90是减速比，4是四倍频
//uint16_t jsb = 5280;//11x30x4,电机的输出轴转一圈产生的脉冲数量。11是电机霍尔转动一圈的脉冲数量，90是减速比，4是四倍频

int setpoint = 60;//设置目标转速  单位RPM


//目标转速转换成脉冲数量，因为最后PID控制的是脉冲数量，转换成50ms需要的脉冲数量。
#define Set_Moto_A  setpoint*jsb/1200
#define Set_Moto_B  setpoint*jsb/1200
int Moto_A,Moto_B;      //PWM占空比

/*
********************************************************************************************************
函数名称：void TIM1_UP_IRQHandler(void)
函数功能：Time1定时器1中断服务函数   10ms定时
硬件连接：
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void SysTick_Handler(void)
{
		LED_Flash(50);//500ms闪烁一次
		OLED_Timer1++;
		OLED_Timer2++;
		Encoder_Timer++;
		
		//电机转速50ms采样一次	
		if(Encoder_Timer>=5)
		{
			Encoder_Timer = 0;
			Encoder_A=-Read_Encoder(2);                        //读取编码器，计算出变化量
			Encoder_B=Read_Encoder(3);                   //读取编码器，计算出变化量,负号是因为两个电机 相对位置180°
			
			//PID计算，计算出的数去调节pwm占空比
			Moto_A = PID_PositionPidA(Set_Moto_A,Encoder_A);
			Moto_B = PID_PositionPidA(Set_Moto_B,Encoder_B);
			//PWM占空比给定时器，控制电机
			Motor_A_SetPWM(Moto_A);	
				Motor_B_SetPWM(Moto_B);
			//编码器脉冲数转换成圈数 单位RPM
			//50ms采样一次，1200就一分钟，1320就是11x30x4和电机有关，11表示电机霍尔一圈的脉冲数量，30是减速比，4是stm32的编码器4倍频 
			Speed_A=Encoder_A*1200/jsb;
			Speed_B=Encoder_B*1200/jsb;
			

		}
		
		
		//OLED显示更新 更新速度
		if(OLED_Timer1 >= 100)//1S 更新一次速度
		{	
			OLED_Timer1=0;
			OLED_Speed_Flag = 1;
		}
		
		//OLED显示 更新ADC值
		if(OLED_Timer2 >= 200)//2S 更新一次ADC
		{
			ADC_BAT_Val = Get_BAT_ADC();//ADC 采样 电池电压
			ADC_SYS_Val =  Get_SYS_ADC();//aDC 采样 系统电压

			OLED_Timer2=0;
			OLED_ADC_Flag = 1;
		}
	
		
}



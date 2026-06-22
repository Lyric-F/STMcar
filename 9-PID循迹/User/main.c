/*
********************************************************************************************************
文件名：main.c
功  能：
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

/*
********************************************************************************************************
更新日志：
1.2017-2-8，增加EEPROM测试函数
2.2017-2-8，增加uart测试函数
3.2017-2-8，增加oled测试函数
*********************************************************************************************************
*/
#include "bsp_sys.h"
#include "stdio.h"

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
//***************************设置局部变量***************************//
extern u16 ADC_BAT_Val;
extern u16 ADC_SYS_Val;
	
float adc1_B;
float adc2_S;

char adc1_BAT[5];
char adc2_SYS[4];

unsigned char UART1_BUF[16];
	
extern int Speed_A,Speed_B;
extern u8 OLED_ADC_Flag;
extern u8 OLED_Speed_Flag;
	
extern int Moto_A;
extern float Integral;
extern int setpoint;
extern float Car_LC;
char LC[8];


//*****************************************************************//
	
//*****************************系统初始*****************************//
	
	STM32_System_Init();//所有系统配置在这个函数里完成
	
//*****************************************************************//

		while (1)
		{
//						//虚拟示波器显示，#if 0 失效，#if 1有效。
//			#if 1
//			//打印A电机的实际速度（转速），打印B电机的实际速度（转速），设置的目标速度
//			printf("%d,%d,%d,%d\n",Speed_A,Speed_B,setpoint);
//			
//			#endif
			

			
		//速度1S显示一次
			if(OLED_Speed_Flag == 1)
			{
				OLED_Speed_Flag = 0;
				OLED_ShowNumZF(16,1,Speed_B,4,12);	//显示B电机实际转速
				OLED_ShowNumZF(80,1,Speed_A,4,12);	//显示A电机实际转速
				OLED_ShowNumZF(32,2,setpoint,4,12); //显示设置目标转速
				sprintf(LC,"%6.2f",Car_LC);
				OLED_ShowString(24,3, LC,12);  //显示里程
			}	
		
		//电压2S显示一次
		if(OLED_ADC_Flag==1)
		{
			OLED_ADC_Flag=0;
			adc1_B=ADC_BAT_Val*3.3/4096*11;
			sprintf(adc1_BAT,"%2.1f",adc1_B);
		  OLED_ShowString(16,0, adc1_BAT,12);  //OLED显示电池电压

			adc2_S=ADC_SYS_Val*3.3/4096*2;
			sprintf(adc2_SYS,"%2.1f",adc2_S);
		  OLED_ShowString(96,0, adc2_SYS,12);  //OLED显示电池电压	
		}
		
 
	}	
	
}	



/*********************************************END OF FILE**********************/

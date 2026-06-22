#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"

/*
********************************************************************************************************
函数名称：void SysTick_Init(void)
函数功能：配置滴答定时器中断，作为整个系统的定时用
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
			SystemFrequency / 100    10ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 100))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
}




/*
********************************************************************************************************
文件名：PID.c
功  能：
备  注：
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/
#include "PID.h"

//A电机PID参数
float MotorA_kp=300;  
float MotorA_ki=50;    
float MotorA_kd=0;  
//B电机PID参数
float MotorB_kp=300;  
float MotorB_ki=50;    
float MotorB_kd=0; 

int16_t MotorF_kp=600;  
int16_t MotorF_ki=0;    
int16_t MotorF_kd=50; 


float Scale =0.1;//10倍
float Integral;//用于示波器显示积分量

/*
********************************************************************************************************
函数名称：int16_t PID_PositionPidA(int16_t Ptn_Target, int16_t Ptn_Current)
函数功能：位置PID,用于A电机
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出					
硬件连接：	
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
float PID_PositionPidA(int16_t Ptn_Target, int16_t Ptn_Current)
{
	float Motor_Pwm_Out;
	static float Error,Error_last,Error_integral = 0;
	Error = Ptn_Target - Ptn_Current;
	Error_integral += Error;//积分
	Integral =Error_integral;//用于虚拟示波器vofa显示
	
	if(Error_integral>2000)                       //积分限幅     
	Error_integral=2000;
	if(Error_integral<-2000)                        //积分限幅     
	Error_integral=-2000;

	Motor_Pwm_Out = Scale * MotorA_kp*Error + 
									Scale * MotorA_ki*Error_integral + 
									Scale * MotorA_kd*(Error-Error_last);
	
	Error_last = Error;	
	
	if(Motor_Pwm_Out>=7100)Motor_Pwm_Out=7100;
	if(Motor_Pwm_Out<=-7100)Motor_Pwm_Out=-7100;
	return Motor_Pwm_Out;
}	
/*
********************************************************************************************************
函数名称：int16_t PID_PositionPidB(int16_t Ptn_Target, int16_t Ptn_Current)
函数功能：位置PID，用于B电机
					
硬件连接：	
备    注：
日    期: 2017-2-6
*********************************************************************************************************
*/
float PID_PositionPidB(int16_t Ptn_Target, int16_t Ptn_Current)
{
	float Motor_Pwm_Out;
	static float Error,Error_last,Error_integral = 0;
	Error = Ptn_Target - Ptn_Current;
	
	Error_integral += Error;//积分
	//Integral =Error_integral;//用于虚拟示波器vofa显示
	
	if(Error_integral>2000)                        //积分限幅     
	Error_integral=2000;
	if(Error_integral<-2000)                       //积分限幅     
	Error_integral=-2000;
	
	Motor_Pwm_Out = Scale * MotorB_kp*Error + Scale * MotorB_ki*Error_integral + Scale * MotorB_kd*(Error-Error_last);
	Error_last = Error;	
	
	if(Motor_Pwm_Out>=7100)Motor_Pwm_Out=7100;
	if(Motor_Pwm_Out<=-7100)Motor_Pwm_Out=-7100;
	return Motor_Pwm_Out;
}	



float PID_PositionPidFind(int Ptn_State, int Ptn_Current)
{
	float Motor_Pwm_Out;
	static float bias,bias_last,bias_integral = 0;
	bias = Ptn_State - Ptn_Current;
	bias_integral += bias;
	if(bias_integral>2000)                       //积分限幅     
	bias_integral=2000;
	if(bias_integral<-2000)
	bias_integral=-2000;
	
	Motor_Pwm_Out = MotorF_kp*bias*Scale + MotorF_ki*bias_integral*Scale + MotorF_kd*(bias-bias_last)*Scale;

	bias_last = bias;	
	
	return Motor_Pwm_Out;
}	


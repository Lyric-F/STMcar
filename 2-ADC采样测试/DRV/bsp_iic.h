#ifndef __BSP_IIC_H
#define __BSP_IIC_H
#include "stm32f10x.h"
///*
//********************************************************************************************************
//文件名：iic.c
//功  能：IIC初始化与读写的函数
//淘  宝：https://shop60670850.taobao.com
//作  者：lilianhe
//日  期: 2017-2-6
//*********************************************************************************************************
//*/



#include "bsp_iic.h"

void IIC_Read(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pBuf, uint16_t num);
void IIC_Write(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pBuf, uint16_t num);
void IIC_ReadByte(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pData);
void IIC_WriteByte(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
void IIC_Init(void);


#endif

















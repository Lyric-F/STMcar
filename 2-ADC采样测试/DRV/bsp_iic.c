/*
********************************************************************************************************
文件名：bsp_iic.c
功  能：IIC通信底层
备  注：硬件iic
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/
#include "bsp_iic.h"

/*
********************************************************************************************************
更新日志：
1.2017-2-8，使用PB10----SCL，PB11----SDA


*********************************************************************************************************
*/



/*
 *  I2C 读取一个缓冲区
    I2C：I2C端口
    dev_addr：设备地址（需要左移移位）
    reg_addr：寄存器地址
    pBuf：读取的缓冲区
    num：读取数据的大小
*/
void IIC_Read(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pBuf, uint16_t num)
{
    /* 等待总线空闲 */
    while(RESET != I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)){}

    /* 产生起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Transmitter);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

    /* 发送寄存器地址 */
    I2C_SendData(I2C, reg_addr);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

    /* 重复起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Receiver);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){}

    /*使能 ACK */
    I2C_AcknowledgeConfig(I2C, ENABLE);
        
    while(num > 1)
    {
        /* 等待数据接收 */
        while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
        *pBuf = I2C_ReceiveData(I2C);

        num--;
        pBuf++;
    }

    /* 在最后一个字节读取前，提前打开 NACK */
    I2C_AcknowledgeConfig(I2C, DISABLE);

    /* 在最后一个字节读取前， 提前使能结束位 */
    I2C_GenerateSTOP(I2C, ENABLE);

    /* 最后一个字节 */
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
    *pBuf = I2C_ReceiveData(I2C);

}


/*
 *  I2C 写入一个缓冲区
    I2C：I2C端口
    dev_addr：设备地址（需要左移移位）
    reg_addr：寄存器地址
    pBuf：写入的缓冲区
    num：写入数据的大小
*/
void IIC_Write(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pBuf, uint16_t num)
{
    /* 等待I2C总线空闲 */
    while(RESET != I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)){}

    /* 产生起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送从设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Transmitter);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

    /* 写寄存器地址 */
    I2C_SendData(I2C, reg_addr);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)){}

    /* 写数据 */
    while(num > 1)
    {
        I2C_SendData(I2C, *pBuf);
        while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)){}
        num--;
        pBuf++;
    }

    /* 最后一个字节 */
    I2C_SendData(I2C, *pBuf);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

    /* 产生结束位 */
    I2C_GenerateSTOP(I2C, ENABLE);
}


/*
 *  I2C 读取一个字节
    I2C：I2C端口
    dev_addr：设备地址（需要左移移位）
    reg_addr：寄存器地址
    data：读取的值
*/
void IIC_ReadByte(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pData)
{
    /* 等待总线空闲 */
    while(RESET != I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)){}

    /* 产生起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Transmitter);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

    /* 发送寄存器地址 */
    I2C_SendData(I2C, reg_addr);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

    /* 重复起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Receiver);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){}

    /* NACK */
    I2C_AcknowledgeConfig(I2C, DISABLE);

    /* 结束 */
    I2C_GenerateSTOP(I2C, ENABLE);

    /* 等待数据接收 */
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
    *pData = I2C_ReceiveData(I2C);
}



/*
 *  I2C 写入一个字节
    I2C：I2C端口
    dev_addr：设备地址（需要左移移位）
    reg_addr：寄存器地址
    data：写入的值
*/
void IIC_WriteByte(I2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    /* 等待I2C总线空闲 */
    while(RESET != I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)){}

    /* 产生起始位 */
    I2C_GenerateSTART(I2C, ENABLE);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)){}

    /* 发送从设备地址 */
    I2C_Send7bitAddress(I2C, dev_addr, I2C_Direction_Transmitter);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

    /* 写寄存器地址 */
    I2C_SendData(I2C, reg_addr);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING)){}

    /* 写数据 */
    I2C_SendData(I2C, data);
    while(ERROR == I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

    /* 产生结束位 */
    I2C_GenerateSTOP(I2C, ENABLE);
}


/*
 * I2C 初始化
*/
void IIC_Init(void)
{
    /* IIC 与 GPIO配置结构体 */
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef   I2C_InitStructure;

    /* 使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* 引脚配置 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 起始设置高电平 */
    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);

    /* IIC 配置 I2C2--用于与MPU6050通信, OLED通信 */
    I2C_InitStructure.I2C_ClockSpeed = 400000;                                  /* 400K */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                                  /* IIC 模式 */
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;                          /* 2倍周期 */
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                                 /* 使能ACK */
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   /* 7bit */
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                                   /* 自身地址 */
    I2C_Init(I2C2, &I2C_InitStructure);

    /* I2C使能 */
    I2C_Cmd(I2C2, ENABLE);
}


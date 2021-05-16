
#include <iostream>
#include "SoftI2C_Driver.h"

/*
Change by your Project
*/
void SoftI2C_Class::I2C_SDA_Pin_Config(char select_type)
{
	if (select_type == IN_TYPE)
	{
		/** Do Your Own Mcu SDA Config, must be in floating mode **/
		/*GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);*/
	}
	else if (select_type == OUT_TYPE)
	{
		/** Do Your Own Mcu SDA Config, must be out mode **/
		/*GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);*/
	}
}

/*
Change by your Project
*/
void SoftI2C_Class::Delay_US(int time_val)
{
	// write your us Delay Func connect your MCU freq
}

/**********************************************************************************************************************************/

void SoftI2C_Class::I2C_Init(void)
{
	I2C_BUS_PWROFF;
	I2C_SDA_Pin_Config(OUT_TYPE);
	PIN_SDA_HIGH;
	PIN_SCL_HIGH;
	Delay_US(500);
	I2C_BUS_PWRON;
}

void SoftI2C_Class::Read_Device_Datas(volatile unsigned char* I2C_buffer, char Addr, char Sum_Req)
{
	I2C_SDA_Pin_Config(OUT_TYPE);
	Start_Com();
	Send_7bit_Address(DEVICE_ADDR, WRITE_REQ);
	I2C_SendData(Addr);
	Stop_Com();
	Start_Com();
	Send_7bit_Address(DEVICE_ADDR, READ_REQ);
	I2C_ReadData(I2C_buffer, Sum_Req);
	Stop_Com();
}

void SoftI2C_Class::Write_Device_Datas(unsigned char I2C_buffer, unsigned char addr)
{
	I2C_SDA_Pin_Config(OUT_TYPE);
	Start_Com();
	Send_7bit_Address(DEVICE_ADDR, WRITE_REQ);
	I2C_SendData(addr);
	I2C_SendData(I2C_buffer);
	Stop_Com();
}

unsigned char SoftI2C_Class::Send_7bit_Address(unsigned char DevAddress, unsigned char RW_Stade)
{
	unsigned char Clock_Cnt = 7, ACK;

	for (Clock_Cnt = 7; Clock_Cnt >= 0; Clock_Cnt--)
	{
		if (DevAddress & (0x01 << Clock_Cnt))
			PIN_SDA_HIGH;
		else
			PIN_SDA_LOW;

		Clock_Active();
	}

	if (RW_Stade == READ_REQ)
		PIN_SDA_HIGH;
	else
		PIN_SDA_LOW;

	Clock_Active();

	I2C_SDA_Pin_Config(IN_TYPE);

	Clock_Active();

	ACK = READ_PIN_SDA;

	I2C_SDA_Pin_Config(OUT_TYPE);

	return ACK;
}

unsigned char SoftI2C_Class::I2C_ReadData(volatile unsigned char* pBuffer, unsigned char count)
{
	unsigned char Clock_Cnt = 0 , Data_Cnt = 0;

	I2C_SDA_Pin_Config(WRITE_REQ);

	for(Data_Cnt = count ; Data_Cnt >= 0 ; Data_Cnt--)
	{
		*pBuffer = 0;

		for(Clock_Cnt = 7 ; Clock_Cnt >= 0 ; Clock_Cnt--)
		{
			if (READ_PIN_SDA)
				*pBuffer = *pBuffer | (0x01 << Clock_Cnt);

			Clock_Active();
		}

		if (Data_Cnt > 0)
		{
			I2C_SDA_Pin_Config(OUT_TYPE);
			PIN_SDA_LOW;
			Clock_Active();
			pBuffer++;
			I2C_SDA_Pin_Config(IN_TYPE);
		}
	}

	I2C_SDA_Pin_Config(OUT_TYPE);
	PIN_SDA_HIGH;
	Clock_Active();

	return *pBuffer;
}

unsigned char SoftI2C_Class::I2C_SendData(unsigned char reg_adr)
{
	unsigned char Clock_Cnt = 7, ACK;

	for(Clock_Cnt = 7 ; Clock_Cnt >= 0 ; Clock_Cnt--)
	{
		if (reg_adr & (0x01 << Clock_Cnt))
			PIN_SDA_HIGH;
		else
			PIN_SDA_LOW;

		Clock_Active();
	}

	I2C_SDA_Pin_Config(IN_TYPE);

	Clock_Active();

	ACK = READ_PIN_SDA;

	I2C_SDA_Pin_Config(OUT_TYPE);

	return ACK;
}

void SoftI2C_Class::Clock_Active(void)
{
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
	PIN_SCL_HIGH;
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
	PIN_SCL_LOW;
}

void SoftI2C_Class::Start_Com(void)
{
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
	PIN_SDA_LOW;
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
	PIN_SCL_LOW;
}

void SoftI2C_Class::Stop_Com(void)
{
	PIN_SDA_HIGH;
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
	PIN_SCL_HIGH;
	Delay_US(SIGNAL_PERIOD_TIMEOUT);
}














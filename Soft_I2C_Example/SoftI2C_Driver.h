#pragma once
/*
*
* This ProjectThe purpose of this presentation is testing and education.
* You can integrate it into your commercial projects. It is open to development.
*
* You can contact me if you have any comments or questions.
*
*
* Developed By Ali Şahbaz
* 16.05.2021
* ali_sahbaz@outlook.com
*/

/*
Change by your Project, Define your Pins and Stades
*/
#define PIN_SDA_LOW    0//GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define PIN_SDA_HIGH   0//GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define PIN_SCL_LOW    0//GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define PIN_SCL_HIGH   0//GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define READ_PIN_SDA   0//GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
//I2C Device Power
#define I2C_BUS_PWRON	0//GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define I2C_BUS_PWROFF	0//GPIO_ResetBits(GPIOC,GPIO_Pin_0)
//Your device's Adress
#define DEVICE_ADDR    0x50
//Wait Timeout for signal freq
#define SIGNAL_PERIOD_TIMEOUT       5
// Static Parts
#define IN_TYPE        0
#define OUT_TYPE       1
#define WRITE_REQ      0
#define READ_REQ       1

class SoftI2C_Class {

public:

	void I2C_Init(void);
	unsigned char I2C_SendData(unsigned char reg_adr);
	unsigned char I2C_ReadData(volatile unsigned char* pBuffer, unsigned char count);
	void Write_Device_Datas(unsigned char I2C_buffer, unsigned char addr);
	void Read_Device_Datas(volatile unsigned char* I2C_buffer, char Addr, char Sum_Req);
	void I2C_SDA_Pin_Config(char select_type);
	void Delay_US(int time_val);
	void Clock_Active(void);
	void Start_Com(void);
	void Stop_Com(void);
	unsigned char Send_7bit_Address(unsigned char DevAddress, unsigned char RW_Stade);

private:

};
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
#include <iostream>
#include "SoftI2C_Driver.h"
#include "FDC1004_Test_Driver.h"


int main()
{
	FDC1004_Class Fdc1004;

	Fdc1004.FDC._addr_shift = DEVICE_ADDR << 1;

	SoftI2C_Class SoftI2C;

	SoftI2C.I2C_Init();

	/*
	Do your own I2C Device Configs
	Use -> Write_Device_Datas(buf,adrr); and x = Read_Device_Datas(buf,addr,cnt)
	*/

	while (1)
	{
		Fdc1004.FDC1004_Task_Manager(SoftI2C);
	}

}


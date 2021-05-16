#include <iostream>
#include "SoftI2C_Driver.h"
#include "FDC1004_Test_Driver.h"

#define FDC1004_CAPDAC_MAX      31
#define UPPER_BOUND             16384
#define LOWER_BOUND             -16384

#define MAIN_CONTROL_STEP                 0
#define TRIG_SINGLE_MEASURE_CONFIG        1
#define WAIT_STEP                         2
#define MEASURE_STEP                      3
#define CALCULATE_STEP                    4


void FDC1004_Class::FDC1004_Task_Manager(SoftI2C_Class softI2C)
{
	double capacitance = 0;
	short configuration_data;
	uint8_t value[3];

	switch (FDC.STEP)
	{
	case MAIN_CONTROL_STEP:

		/*
		Add your own Control Step Bloks and Manage
		Do your Capacitance Step Stades Staffs here
		*/

		Goto_Step(TRIG_SINGLE_MEASURE_CONFIG);

		break;

	case TRIG_SINGLE_MEASURE_CONFIG:

		configuration_data = ((uint16_t)0) << 13; //CHA
		configuration_data |= ((uint16_t)0x04) << 10; //CHB disable / CAPDAC enable
		configuration_data |= ((uint16_t)FDC.CAPACITANCE_VALUE) << 5; //CAPDAC value
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 0);
		softI2C.I2C_SendData(0x08);
		softI2C.I2C_SendData((uint8_t)(configuration_data >> 8));
		softI2C.I2C_SendData((uint8_t)configuration_data);
		softI2C.Stop_Com();
		//triggerSingleMeasurement
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 0);
		softI2C.I2C_SendData(0x0C);
		softI2C.I2C_SendData(0x04);
		softI2C.I2C_SendData(0x80);
		softI2C.Stop_Com();
		Goto_Step(WAIT_STEP);
		break;

	case WAIT_STEP:

		if (FDC.Timer > 10)
			Goto_Step(MEASURE_STEP);
		break;

	case MEASURE_STEP:
		//msb
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 0);
		softI2C.I2C_SendData(0x00);
		softI2C.Stop_Com();
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 1);
		softI2C.I2C_ReadData(value, 2);
		softI2C.Stop_Com();
		FDC.real_Val1 = value[0] << 8;
		FDC.real_Val1 |= value[1];
		//lsb
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 0);
		softI2C.I2C_SendData(0x01);
		softI2C.Stop_Com();
		softI2C.I2C_SDA_Pin_Config(OUT_TYPE);
		softI2C.Start_Com();
		softI2C.Send_7bit_Address(FDC._addr_shift, 1);
		softI2C.I2C_ReadData(value, 2);
		softI2C.Stop_Com();
		FDC.real_Val2 = value[0] << 8;
		FDC.real_Val2 |= value[1];
		Goto_Step(CALCULATE_STEP);
		break;

	case CALCULATE_STEP:
		double capacitance = 0;
		capacitance = ((int32_t)457) * ((int32_t)FDC.real_Val1);
		capacitance /= 1000;
		capacitance += ((int32_t)3028) * ((int32_t)FDC.CAPACITANCE_VALUE);
		capacitance = capacitance / 1000;
		if (FDC.real_Val1 > UPPER_BOUND)
		{
			if (FDC.CAPACITANCE_VALUE < FDC1004_CAPDAC_MAX)
				FDC.CAPACITANCE_VALUE++;
		}
		else if (FDC.real_Val1 < LOWER_BOUND)
		{
			if (FDC.CAPACITANCE_VALUE > 0)
				FDC.CAPACITANCE_VALUE--;
		}
		Goto_Step(MAIN_CONTROL_STEP);
		break;

		/*default:
			Goto_Step(MAIN_CONTROL_STEP);
			break;*/
	}

}


void FDC1004_Class::Goto_Step(int step)
{
	FDC.STEP = step;
	FDC.Timer = 0;
}

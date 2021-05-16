#pragma once

typedef struct fdc1004_Params {

	char _addr_shift;

	int16_t real_Val1, real_Val2;

	int CAPACITANCE_VALUE = 0;

	char STEP;

	/*
	Change by your Project, Timer Count must be increase 1 ms Timer
	*/
	unsigned int Timer;

};



class FDC1004_Class {

public:

	fdc1004_Params FDC;

	void FDC1004_Task_Manager(SoftI2C_Class softI2C);

private:

	void Goto_Step(int step);

};
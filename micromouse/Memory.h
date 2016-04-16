#pragma once

#ifdef __MK20DX256__ // Teensy Compile
	#include <EEPROM.h>
#endif

namespace Micromouse {

	//0-99 unreserved


	/* 
	100 - 179: IRSensor Calibration Data Block 
	relative to the starting address
	0: calibrationSize
	1: calibrationStart
	2: calibrationInterval
	3-19: CalibrationData[]
	*/
	const int IR_FRONT_LEFT_MEMORY = 100;//-119
	const int IR_FRONT_RIGHT_MEMORY = 200;//-139
	const int IR_LEFT_MEMORY = 300;//-159
	const int IR_RIGHT_MEMORY = 400;//-179


	//180-511 unreserved

	//512-2047 map



	class Memory
	{
	public:
		static int read(int address);
		static void write(int address, int val);

	private:
		Memory() {};//dont instantiate me

	};
}

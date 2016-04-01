#pragma once

#ifdef __MK20DX256__
// If compiled for Teensy
#include <Encoder.h>

namespace Micromouse
{

	//Motor is a class that can be used to set the direction and speed of a motor,
	//and to get information from its encoder.
	class Motor
	{
	public:
		Motor();

	private:
		int fwdPin;
		int backPin;
		int pwmPin;
		int encoderPin;
	};

}

#endif

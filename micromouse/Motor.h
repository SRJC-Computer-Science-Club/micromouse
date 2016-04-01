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
		Motor(int fwdPin, int bwdPin, int pwmPin, int fwdEncoderPin, int bwdEncoderPin);

		//Moves the motor for a number of encoder counts.
		//One encoder count is equal to 1/16 rotation.
		//If counts is negative, the motor will move backwards.
		//The motor will accelerate linearly until speed is reached, for rampTime seconds.
		//Then the motor will deccelerate linearly until it stops, for rampTime seconds.
		//speed should be between 0 and 1. With 1 being the maximum speed of the motor.
		void moveMotor(int counts, float targetSpeed, float rampTime);

	private:
		void initPins();

		int fwdPin;			//Forward pin
		int bwdPin;			//Backward pin
		int pwmPin;			//Pulse-width modulation pin (for speed control)

		Encoder encoder;
	};

}

#endif

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
		//void move(int counts, float targetSpeed, float rampTime);

		//speed should be a value between -1 and 1.
		//Positive speeds move the motor forward. Negative speeds move it backward.
		//The actual speed of the motor will be the product of speed and maxSpeed ( see setMaxSpeed()).
		void setMovement(float speed);

		//Sets the maximum speed of the motor.
		//All speeds given will be multiplied by this factor.
		void setMaxSpeed(float maxSpeed);

		//Turns off the motor and brakes.
		void brake();

		//Turns off the motor and coasts.
		void coast();
		
		//Returns the number of encoder counts since resetCounts() was last called.
		int getCounts() const;

		//Returns the number of encoder counts since resetCounts() was last called.
		//Then resets the encoder count.
		int resetCounts();
	private:
		void initPins();

		float maxSpeed = 1.0f;

		int fwdPin;			//Forward pin
		int bwdPin;			//Backward pin
		int pwmPin;			//Pulse-width modulation pin (for speed control)

		Encoder encoder;
	};

}

#endif

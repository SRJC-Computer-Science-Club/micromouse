#pragma once

//#include <string>

#ifdef __MK20DX256__ // Teensy Compile
	#include <Encoder.h>
#endif

namespace Micromouse
{
	//Motor is a class that can be used to set the direction and speed of a motor,
	//and to get information from its encoder.
	class Motor
	{
	public:
		const float CALIBRATION_TIMEOUT_SEC = 0.5f;

		Motor(int fwdPin, int bwdPin, int pwmPin, int fwdEncoderPin, int bwdEncoderPin);

		//Loads calibration data from memory.
		void loadCalibration();

		//Saves calibration data to memory.
		void saveCalibration();

		//Spins the motor forward and backward, calibrating minFwdVoltage and minBwdVoltage,
		//which are each set to the lowest speed that still turns the motor.
		void calibrate();

		//speed should be a value between -1 and 1.
		//Positive speeds move the motor forward. Negative speeds move it backward.
		//The actual speed of the motor will be the product of speed and maxSpeed ( see setMaxSpeed()).
		void setMovement(float speed);

		//maxSpeed should be a float between 0 and 1;
		//Sets the maximum speed of the motor.
		//All speeds given will be multiplied by this factor.
		void setMaxSpeed(float maxSpeed);

		//Returns the maxSpeed of the motor.
		float getMaxSpeed() const;

		//Turns off the motor and brakes.
		void brake();

		//Turns off the motor and coasts.
		void coast();

		//Returns the number of encoder counts since resetCounts() was last called.
		int getCounts();

		//Returns the number of encoder counts since resetCounts() was last called.
		//Then resets the encoder count.
		int resetCounts();

	private:
		void initPins();

		int calibrateMinVoltage();

		void setVoltage(int voltage, bool fwd);

		float maxSpeed = 1.0f;

		//The minimum speed that still turns the motor (forward)
		int minFwdVoltage = 0;
		//The minimum speed that still turns the motor (backward)
		int minBwdVoltage = 0;

		int fwdPin;			//Forward pin
		int bwdPin;			//Backward pin
		int pwmPin;			//Pulse-width modulation pin (for speed control)

#ifdef __MK20DX256__ // Teensy Compile
		Encoder encoder;
#endif
	};
}

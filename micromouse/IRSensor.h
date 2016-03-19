#pragma once
#include <assert.h>

namespace Micromouse
{

	// The IRSensor class represents a single IR sensor
	// it contains information about the min and max range
	// it can perform calibrations and provides default calibrations
	// it can calculate distance using analogRead values
	// it does this through linear interpolation of the calibration data

	// when not compiled on a teensy calibration has no effect
	// and default calibration dat is always used

	// when not compiled on a teensy getDistance will always return the same value

	class IRSenor
	{
	public:
		IRSenor(int pin, int minRange, int maxRange);
		~IRSenor();

		bool calibrate( int calibrationStart, int calibrationInterval );

		// returns the distance in mm
		// will return a value between MIN_RANGE and MAX_RANGE
		int getDistance(); 


	private:
		void defaultCalibration();
		float interpolate(int x1, int x2, int y1, int y2, int x);

		const int PIN; //pin to read analog data
		const int MIN_RANGE; //min distance for sensor in mm
		const int MAX_RANGE; //max distance for sensor in mm

		//TODO use real pin;
#ifdef __MK20DX256__ //this is the Teensy signature
		//comment line below to test compile, remove #error when pins have been set
#error define correct pin number 
#endif
		const int BUTTON_PIN = 10;

		int calibrationStart; //distance for calibration to begin at in mm
		int calibrationInterval; //the interval between calibrations in mm
		int calibrationSize; //the number of calibration data points

		int * calibrationData; //stores the calibration data
	};
}




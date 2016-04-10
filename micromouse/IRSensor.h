#pragma once
#include <assert.h>
#include "Memory.h"

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

	class IRSensor
	{
	public:
		IRSensor(int pin, int minRange, int maxRange);
		~IRSensor();

		bool calibrate( int calibrationStart, int calibrationInterval );
		bool loadCalibration( int address );
		void saveCalibration( int address );

		// returns the distance in mm
		// will return a value between MIN_RANGE and MAX_RANGE
		float getDistance(); 


	private:
		void defaultCalibration();
		float interpolate(int x1, int x2, int y1, int y2, int x);

		const int DATA_PIN; //pin to read analog data
		const int MIN_RANGE; //min distance for sensor in mm
		const int MAX_RANGE; //max distance for sensor in mm

		int calibrationStart; //distance for calibration to begin at in mm
		int calibrationInterval; //the interval between calibrations in mm
		int calibrationSize; //the number of calibration data points

		int * calibrationData; //stores the calibration data
	};
}




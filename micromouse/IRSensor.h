#pragma once
#include <assert.h>

namespace Micromouse
{
	class IRSenor
	{
	public:
		IRSenor(int pin, int minRange, int maxRange);
		~IRSenor();

		bool calibrate( int calibrationStart, int calibrationInterval );
		int getDistance(); //returns distance in millimeters

	private:
		void initCalibration();
		float interpolate(int x1, int x2, int y1, int y2, int x);
		const int PIN;
		const int MIN_RANGE;
		const int MAX_RANGE;

		//TODO use real pin;
#ifdef __MK20DX256__ //this is the Teensy signature
		//comment line below to test compile, remove #error when pins have been set
#error define correct pin number 
#endif
		const int BUTTON_PIN = 10;

		int calibrationStart;
		int calibrationInterval;
		int calibrationSize;

		int * calibrationData;
	};
}




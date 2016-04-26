#pragma once
#include "Controller.h"
#include "Logger.h"
#include <vector>
#include "Timer.h"



namespace Micromouse
{
	class LEDController
	{
	public:
		Controller();
		~Controller();

		//this is a blocking function
		// blinks the led 'reps' number of times
		int blinkLED(int reps = 1, int timeOn = 80, int timeOff = 50);

		// this is a blocking function
		// perfomrs a countdown and blinks the led
		void blinkLEDCountdown(int sec);
	};
}
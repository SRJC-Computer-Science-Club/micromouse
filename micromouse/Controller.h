#pragma once
#include "MouseBot.h"



namespace Micromouse
{
	class Controller
	{
	public:
		Controller();
		~Controller();

	private:
		enum states { NONE, MAP_MAZE, RUN_MAZE, SELECT_SPEED, DEBUG_MODE, CAL_SENSORS, CAL_MOTOR, RESET_MAZE };
		
		void debug();
		void runMainLoop();

		void runState();
		void updateState();

		void initPins();
		//this is a blocking function
		// blinks the led 'reps' number of times
		int blinkLED(int reps = 1, int timeOff = 150, int timeOn = 180);

		// this is a blocking function
		// perfomrs a countdown and blinks the led
		void blinkLEDCountdown(int sec);

		void waitForButton();

		MouseBot mouse;

		states state;

		bool doneMap = false;
	};
}
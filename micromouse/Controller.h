#pragma once
#include "LEDController.h"
#include "MouseBot.h"
#include "RobotIO.h"


namespace Micromouse
{
	class Controller
	{
	public:
		Controller();
		~Controller();

	private:
		enum states { NONE, MAP_MAZE, RUN_MAZE, SELECT_SPEED, NONE_4, CAL_SENSORS, CAL_MOTOR, RESET_MAZE };
		
		void debug();
		void runMainLoop();

		void runState();
		void updateState();

		void waitForButton();
        void initPins();

		MouseBot mouse;

		states state;
        
        LEDController led;
        

		bool doneMap = false;
	};
}

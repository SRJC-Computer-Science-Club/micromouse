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
		enum states { NONE, MAP_MAZE, RUN_MAZE, SELECT_SPEED, NONE_4, CAL_SENSORS, CAL_MOTOR, RESET_MAZE };
		
		void debug();
		void runMainLoop();

		void runState();
		void updateState();

		void waitForButton();

		MouseBot mouse;

		states state;

		bool doneMap = false;
	};
}
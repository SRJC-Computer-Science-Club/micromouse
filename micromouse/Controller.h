#pragma once
#include "MouseBot.h"
#include "Drawable.h" //includes SFML

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

		//this is a blocking function
		// blinks the led 'reps' number of times
		int blinkLED(int reps = 1, int timeOn = 80, int timeOff = 50);

		// this is a blocking function
		// perfomrs a countdown and blinks the led
		void blinkLEDCountdown(int sec);

		void waitForButton();

		MouseBot mouse;

		states state;

		bool doneMap = false;



		void beginSimulation();

#ifdef SFML_GRAPHICS_HPP
		sf::Event event;
		sf::Clock clock;
#endif
	};
}
#pragma once

#include "IRSensor.h"

namespace Micromouse
{
	//A class that contains functions and constants used to communicate with the IO pins of the Teensey 3.2 Microcontroller.
	// ## NOT YET IMPLEMENTED ## 
	class RobotIO
	{
	public:
		RobotIO();
		~RobotIO();

		void moveForward(); // ## NOT YET IMPLEMENTED ## Moves the bot forward by half a cell ( 9 cm ).
		void rotateRight(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the right.
		void rotateLeft(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the left.

		bool isClearForward(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall in front of the bot. Otherwise, returns true.
		bool isClearRight(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall to the right of the bot. Otherwise, returns true.
		bool isClearLeft(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall to the left of the bot. Otherwise, returns true.

	private:
		//TODO use actual pin numbers
#ifdef __MK20DX256__ //this is the Teensy signature
		//comment line below to test compile, remove #error when pins have been set
//#error define correct pin numbers 
#endif
		static const int IR_LEFT_PIN = 1;
		static const int IR_RIGHT_PIN = 2;
		static const int IR_FRONT_LEFT_PIN = 3;
		static const int IR_FRONT_RIGHT_PIN = 4;

		enum IRDirection { LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT };

		void initSensors();

		IRSenor* IRSensors[4];
	};
}
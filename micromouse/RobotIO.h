#pragma once

#include "IRSensor.h"
#include "Vector.h"

namespace Micromouse
{
	//TODO use actual pin numbers
#ifdef __MK20DX256__ //this is the Teensy signature

	//comment line below to test compile, remove #error when pins have been set
	//#error define correct pin numbers 
#endif
    const int IR_LEFT_PIN = 1;
    const int IR_RIGHT_PIN = 2;
    const int IR_FRONT_LEFT_PIN = 3;
    const int IR_FRONT_RIGHT_PIN = 4;
    const int BUTTON_PIN = 10;


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

		bool isClearForward(); // Returns false if the range-finder sensors detect a wall in front of the bot. Otherwise, returns true.
		bool isClearRight(); // Returns false if the range-finder sensors detect a wall to the right of the bot. Otherwise, returns true.
		bool isClearLeft(); // Returns false if the range-finder sensors detect a wall to the left of the bot. Otherwise, returns true.

		void followPath(Path * path);

		void calibrateIRSensors();

	private:

        bool isWallinDirection( direction dir );
	
		enum IRDirection { LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT };

		void initSensors();

		IRSenor* IRSensors[4];
	};
}
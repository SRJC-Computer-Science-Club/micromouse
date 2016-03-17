#pragma once

namespace Micromouse
{
	//A class that contains functions and constants used to communicate with the IO pins of the Teensey 3.2 Microcontroller.
	// ## NOT YET IMPLEMENTED ## 
	class RobotIO
	{
	public:
		RobotIO();

		void moveForward(); // ## NOT YET IMPLEMENTED ## Moves the bot forward by half a cell ( 9 cm ).
		void rotateRight(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the right.
		void rotateLeft(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the left.

		bool isClearForward(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall in front of the bot. Otherwise, returns true.
		bool isClearRight(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall to the right of the bot. Otherwise, returns true.
		bool isClearLeft(); // ## NOT YET IMPLEMENTED ## Returns false if the range-finder sensors detect a wall to the left of the bot. Otherwise, returns true.
	};
}
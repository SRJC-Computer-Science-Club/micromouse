/*********************************\
File:			MouseBot.h
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include "Vector.h"

namespace Micromouse
{
	//A class to be used for keeping track of the robot's position, as well as an interface to the I/O of the robot.
	class MouseBot
	{
	public:
		MouseBot();								// Uses a default position of (0,0)
		MouseBot(int x, int y);					// Sets the position to (x,y)
		MouseBot(PositionVector pos);

		PositionVector getPos();				// Returns the position of the mouse
		direction getFacing();					// Return the direction the mouse is facing.
		void setPos(int x, int y);				// Sets the position to (x,y)
		void setPos(PositionVector pos);		// Sets the position to pos

		void mapMaze();

		bool isClearForward();					// Returns true if there isn't a wall in front of the mouse. Uses a virtual maze for debugging on PC, otherwise it uses the bot's hardware.
		bool isClearRight();					// Returns true if there isn't a wall to the right of the mouse. Uses a virtual maze for debugging on PC, otherwise it uses the bot's hardware.
		bool isClearLeft();						// Returns true if there isn't a wall to the left of the mouse. Uses a virtual maze for debugging on PC, otherwise it uses the bot's hardware.

		void moveForward();						// Moves the mouse forward by 1 node (1/2 cell)
		void turnLeft();						// Moves the mouse forward and to the left, turning 90 degrees.
		void turnRight();						// Moves the mouse forward and to the right, turning 90 degrees.
		void rotateLeft();						// Rotates the mouse in place to the left by 90 degrees.
		void rotateRight();						// Rotates the mouse in place to the right by 90 degrees.
		void rotateToFaceDirection(direction dir); // Rotates the mouse in place until it reaches the given direction.

	private:

		void move(direction dir);

		PositionVector position = PositionVector(0,0);
		direction facing = N;
	};
}
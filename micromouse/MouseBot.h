/*********************************\
File:			MouseBot.h
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include "Vector.h"
#include "RobotIO.h"
#include <stack>
#include "IRSensor.h"
#include "Path.h"
#include "Maze.h"


#ifdef __MK20DX256__ //this is the Teensy signature
#else
#include "VirtualMaze.h"
#endif

namespace Micromouse
{
	//A class to be used for keeping track of the robot's position, as well as an interface to the I/O of the robot.
	class MouseBot
	{
	public:
		MouseBot(int x = 0, int y = 0);					// Sets the position to (x,y)
		~MouseBot();

		PositionVector getPos();				// Returns the position of the mouse
		direction getFacing();					// Return the direction the mouse is facing.
		void setPos(int x, int y);				// Sets the position to (x,y)
		void setPos(PositionVector pos);		// Sets the position to pos

		//Maps out the maze. If on Teensey, it uses the sensors and motors to map a physical maze.
		//Otherwise, it generates a random, virtual maze and uses it to simulate mapping.
		//The mouse will visit every cell.
		//Currently, the mouse ends in a random cell. Later, this function should return the mouse to the start.
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
		void followPath(Path* path);
		void backtrack();

		void lookAround();
		bool isPossibleDirection(direction dir);
		int numPossibleDirections();
		direction pickPossibleDirection();

		Maze maze;

#ifdef __MK20DX256__ //this is the Teensy signature
#else
		VirtualMaze* virtualMaze;
#endif

		RobotIO robotIO;
		std::stack<direction> movementHistory;

		PositionVector position = PositionVector(0,0);
		direction facing = N;
	};
}

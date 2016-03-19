/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "MouseBot.h"
#include <stack>

#define __MK20DX256__

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot()
	{
		MouseBot::MouseBot(0,0);
	}

	MouseBot::MouseBot(int x, int y)
	{
		MouseBot(PositionVector(x, y));
	}

	MouseBot::MouseBot(PositionVector pos)
	{
		setPos(pos);

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO = RobotIO();

#else
		// If compiled for PC

		virtualMaze = new VirtualMaze(31, 31);

#endif

	}

	/**** SET / GET FUNCTIONS ****/

	PositionVector MouseBot::getPos()
	{
		return position;
	}

	direction MouseBot::getFacing()
	{
		return facing;
	}

	void MouseBot::setPos(int x, int y)
	{
		setPos(PositionVector(x, y));
	}

	void MouseBot::setPos(PositionVector pos)
	{
		this->position = pos;
	}

	/**** MAPPING FUNCTIONS ****/

	void MouseBot::mapMaze()
	{
		stack<PositionVector*> choicePositions = stack<PositionVector*>();
		choicePositions.push(new PositionVector(position));
		
		while (!choicePositions.empty())
		{
			PositionVector* pos = choicePositions.top();
			choicePositions.pop();

			
		}
	}

	bool MouseBot::isClearForward()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearForward();

#else
		// If compiled for PC

		return virtualMaze->isOpen(position + facing);

#endif

	}

	bool MouseBot::isClearRight()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearRight();

#else
		// If compiled for PC

		return virtualMaze->isOpen(position + (facing + E));

#endif

	}

	bool MouseBot::isClearLeft()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearLeft();

#else
		// If compiled for PC

		return virtualMaze->isOpen(position + (facing + W));

#endif

	}

	/**** MOVEMENT FUNCTIONS ****/

	void MouseBot::move(direction dir)
	{
		position = position + dir;
	}

	void MouseBot::moveForward()
	{
		move(facing);

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.moveForward();

#endif

	}

	void MouseBot::turnLeft()
	{
		facing = facing + NW;
		moveForward();
		facing = facing + NW;
	}

	void MouseBot::turnRight()
	{
		facing = facing + NE;
		moveForward();
		facing = facing + NE;
	}

	void MouseBot::rotateLeft()
	{
		facing = facing + W;

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.rotateLeft();

#endif
	}

	void MouseBot::rotateRight()
	{
		facing = facing + E;

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.rotateRight();

#endif
	}

	void MouseBot::rotateToFaceDirection(direction dir)
	{
		while (facing != dir)
		{
			direction temp = dir - facing;
			if (temp == NE || temp == E || temp == SE)
			{
				turnRight();
			}
			else
			{
				turnLeft();
			}
		}
	}
}

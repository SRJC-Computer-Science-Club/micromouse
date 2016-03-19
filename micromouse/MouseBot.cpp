/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "MouseBot.h"
#include <stack>

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot()
	{
		setPos(PositionVector(0, 0));
	}

	MouseBot::MouseBot(int x, int y)
	{
		setPos(PositionVector(x, y));
	}

	MouseBot::MouseBot(PositionVector pos)
	{
		setPos(pos);
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

	/**** MOVEMENT FUNCTIONS ****/

	void MouseBot::move(direction dir)
	{
		position = position + dir;
	}

	void MouseBot::moveForward()
	{
		move(facing);
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
	}

	void MouseBot::rotateRight()
	{
		facing = facing + E;
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

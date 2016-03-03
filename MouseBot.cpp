/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include <iostream>
#include "MouseBot.h"

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot()
	{
		setPos(Vector::Pos(0, 0));
	}

	MouseBot::MouseBot(int x, int y)
	{
		setPos(Vector::Pos(x, y));
	}

	MouseBot::MouseBot(Vector::Pos pos)
	{
		setPos(pos);
	}

	/**** SET / GET FUNCTIONS ****/

	Vector::Pos MouseBot::getPos()
	{
		return pos;
	}

	void MouseBot::setPos(int x, int y)
	{
		setPos(Vector::Pos(x, y));
	}

	void MouseBot::setPos(Vector::Pos pos)
	{
		this->pos = pos;
	}

	/**** MOVEMENT FUNCTIONS ****/

	void MouseBot::move(direction dir)
	{

	}

	void MouseBot::moveForward()
	{

	}


}
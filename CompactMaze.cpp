/*********************************\
File:			CompactMaze.cpp
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "CompactMaze.h"
#include <stdlib.h>

namespace Micromouse
{
	// CONSTRUCTOR //
	CompactMaze::CompactMaze(int width, int height) :
		width(width),
		height(height),
		open(FlagMatrix(width, height)),
		explored(FlagMatrix(width, height))
	{

	}


	// SET / GET FUNCTIONS //

	void CompactMaze::setOpen(bool flag, int x, int y)
	{
		open.setFlag(flag, x, y);
	}

	void CompactMaze::setOpen(bool flag, Vector::Pos pos)
	{
		setOpen(flag, pos.x(), pos.y());
	}

	void CompactMaze::setExplored(bool flag, int x, int y)
	{
		explored.setFlag(flag, x, y);
	}
	void CompactMaze::setExplored(bool flag, Vector::Pos pos)
	{ 
		setExplored(flag, pos.x(), pos.y());
	}

	bool CompactMaze::isOpen(int x, int y)
	{
		return open.getFlag(x, y);
	}
	bool CompactMaze::isOpen(Vector::Pos pos)
	{
		return isOpen(pos.x(), pos.y());
	}

	bool CompactMaze::isExplored(int x, int y)
	{
		return open.getFlag(x, y);
	}

	bool CompactMaze::isExplored(Vector::Pos pos)
	{
		return isExplored(pos.x(), pos.y());
	}



	// GENERATION FUNCTIONS //

	void CompactMaze::generateRandomMap()
	{
		setExplored(true, 0, 0);

		Vector::Pos head = Vector::Pos(0, 0);
		direction dir = randomPossibleDirection(head);

		while (dir != NONE)
		{
			head = head + dir;
			setOpen(true, head);
			setExplored(true, head);

			head = head + dir;
			setOpen(true, head);
			setExplored(true, head);

			dir = randomPossibleDirection(head);
		}
		
	}

	direction CompactMaze::randomPossibleDirection(Vector::Pos pos)
	{
		direction possibleDirections[4];
		int numPossibleDirections = 0;

		if (!isExplored(pos + N))
		{
			possibleDirections[numPossibleDirections] = N;
			numPossibleDirections++;
		}
		if (!isExplored(pos + E))
		{
			possibleDirections[numPossibleDirections] = E;
			numPossibleDirections++;
		}
		if (!isExplored(pos + S))
		{
			possibleDirections[numPossibleDirections] = S;
			numPossibleDirections++;
		}
		if (!isExplored(pos + W))
		{
			possibleDirections[numPossibleDirections] = W;
			numPossibleDirections++;
		}

		if (possibleDirections == 0)
		{
			return NONE;
		}

		int r = rand() % numPossibleDirections;
		return possibleDirections[r];
	}
}
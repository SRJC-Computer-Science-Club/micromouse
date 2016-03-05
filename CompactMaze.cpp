/*********************************\
File:			CompactMaze.cpp
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "CompactMaze.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

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

	bool CompactMaze::isOpen(int x, int y) const
	{
		return open.getFlag(x, y);
	}
	bool CompactMaze::isOpen(Vector::Pos pos) const
	{
		return isOpen(pos.x(), pos.y());
	}

	bool CompactMaze::isExplored(int x, int y) const
	{
		return explored.getFlag(x, y);
	}

	bool CompactMaze::isExplored(Vector::Pos pos) const
	{
		return isExplored(pos.x(), pos.y());
	}

	bool CompactMaze::isInsideMaze(int x, int y) const
	{
		return (x >= 0) && (y >= 0) && (x < width) && (y < height);
	}

	bool CompactMaze::isInsideMaze(Vector::Pos pos) const
	{
		return isInsideMaze(pos.x(), pos.y());
	}

	int CompactMaze::getWidth() const
	{
		return width;
	}

	int CompactMaze::getHeight() const
	{
		return height;
	}


	// GENERATION FUNCTIONS //

	void CompactMaze::generateRandomMap()
	{
		setExplored(true, 0, 0);
		setOpen(true, 0, 0);

		Vector::Pos head = Vector::Pos(0, 0);
		direction dir = randomPossibleDirection(head);

		while (dir != NONE)
		{
			setExplored(true, head + N);
			setExplored(true, head + E);
			setExplored(true, head + S);
			setExplored(true, head + W);

			head = head + dir;
			setOpen(true, head);

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

		if (isInsideMaze(pos + N) && !isExplored(pos + N))
		{
			possibleDirections[numPossibleDirections] = N;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + E) && !isExplored(pos + E))
		{
			possibleDirections[numPossibleDirections] = E;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + S) && !isExplored(pos + S))
		{
			possibleDirections[numPossibleDirections] = S;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + W) && !isExplored(pos + W))
		{
			possibleDirections[numPossibleDirections] = W;
			numPossibleDirections++;
		}

		if (numPossibleDirections == 0)
		{
			return NONE;
		}
		else
		{
			int r = rand() % numPossibleDirections;
			return possibleDirections[r];
		}
	}

	ostream& operator<<(ostream& out, const CompactMaze& maze)
	{
		out << endl << "+ ";
		for (int x = 0; x < maze.getWidth(); x++) out << "- ";
		out << "+" << endl;

		for (int y = maze.getHeight() - 1; y >= 0; y--)
		{
			out << "| ";
			for (int x = 0; x < maze.getWidth(); x++)
			{
				if (maze.isExplored(x, y))
				{
					if (maze.isOpen(x, y))
					{
						out << "  ";
					}
					else
					{
						if (y % 2 == 0)
						{
							out << "| ";
						}
						else
						{
							out << "- ";
						}
					}
				}
				else
				{
					out << "+ ";
				}
			}
			out << "|" << endl;
		}

		out << "+ ";
		for (int x = 0; x < maze.getWidth(); x++) out << "- ";
		out << "+" << endl;

		return out;
	}
}
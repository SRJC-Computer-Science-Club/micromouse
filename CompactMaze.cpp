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

		vector<Vector::Pos*> path;
		path.push_back(new Vector::Pos(0, 0));

		while (!path.empty())
		{
			Vector::Pos* temp = path.back();
			Vector::Pos head = Vector::Pos(temp->x(), temp->y());
			path.pop_back();
			delete temp;

			direction dir = randomPossibleDirection(head, path);

			while (dir != NONE)
			{

				head = head + dir;
				setOpen(true, head);
				setExplored(true, head);

				head = head + dir;
				setOpen(true, head);
				setExplored(true, head);

				dir = randomPossibleDirection(head, path);
				cout << path.size() << endl;
			}
			cout << path.size() << endl;
		}
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (x % 2 == 0 || y % 2 == 0)
				{
					setExplored(true, x, y);
				}
			}
		}
	}

	direction CompactMaze::randomPossibleDirection(Vector::Pos pos, vector<Vector::Pos*>& path)
	{
		direction possibleDirections[4];
		int numPossibleDirections = 0;

		if (isInsideMaze(pos + N) && !isExplored(pos + N + N))
		{
			possibleDirections[numPossibleDirections] = N;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + E) && !isExplored(pos + E + E))
		{
			possibleDirections[numPossibleDirections] = E;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + S) && !isExplored(pos + S + S))
		{
			possibleDirections[numPossibleDirections] = S;
			numPossibleDirections++;
		}
		if (isInsideMaze(pos + W) && !isExplored(pos + W + W))
		{
			possibleDirections[numPossibleDirections] = W;
			numPossibleDirections++;
		}

		if (numPossibleDirections > 1)
		{
			path.push_back(new Vector::Pos(pos.x(), pos.y()));
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
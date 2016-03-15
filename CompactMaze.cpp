/*********************************\
File:			CompactMaze.cpp
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "CompactMaze.h"
#include <stdlib.h>
#include <assert.h>

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
		assert(width % 4 == 3 && height % 4 == 3);
	}


	// SET / GET FUNCTIONS //

	void CompactMaze::setOpen(bool flag, int x, int y)
	{
		open.setFlag(flag, x, y);
	}

	void CompactMaze::setOpen(bool flag, PositionVector pos)
	{
		setOpen(flag, pos.x(), pos.y());
	}

	void CompactMaze::setExplored(bool flag, int x, int y)
	{
		explored.setFlag(flag, x, y);
	}
	void CompactMaze::setExplored(bool flag, PositionVector pos)
	{ 
		setExplored(flag, pos.x(), pos.y());
	}

	bool CompactMaze::isOpen(int x, int y) const
	{
		return open.getFlag(x, y);
	}
	bool CompactMaze::isOpen(PositionVector pos) const
	{
		return isOpen(pos.x(), pos.y());
	}

	bool CompactMaze::isExplored(int x, int y) const
	{
		return explored.getFlag(x, y);
	}

	bool CompactMaze::isExplored(PositionVector pos) const
	{
		return isExplored(pos.x(), pos.y());
	}

	bool CompactMaze::isInsideMaze(int x, int y) const
	{
		return (x >= 0) && (y >= 0) && (x < width) && (y < height);
	}

	bool CompactMaze::isInsideMaze(PositionVector pos) const
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

	void CompactMaze::generateRandomMaze()
	{
		//Initializes the starting cell.
		setExplored(true, 0, 0);
		setOpen(true, 0, 0);

		//Create 2x2 end zone in the middle.
		openRegion(PositionVector(width / 2 - 1, height / 2 - 1), 3, 3);
		exploreRegion(PositionVector(width / 2 - 2, height / 2 - 2), 5, 5);

		//path contains every position where a random direction was picked.
		vector<PositionVector*> path;
		path.push_back(new PositionVector(0, 0));

		//Generates the maze
		while (!path.empty())
		{
			int r = rand() % path.size();
			PositionVector* temp = path[r];
			path[r] = path.back();
			path.pop_back();

			PositionVector head = PositionVector(temp->x(), temp->y());
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
			}
		}

		//Opens one wall to the 2x2 finish area in the middle.
		destroyRandomWallInPerimeter(PositionVector(width / 2 - 2, height / 2 - 2), 5, 5);

		//Randomly removes about 1 in 25 walls from the maze.
		for (int i = 0; i < width * height / 50; i++)
		{
			destroyRandomWall();
		}

		//Sets the entire maze as explored.
		exploreRegion(PositionVector(0, 0), width, height);
	}

	void CompactMaze::openRegion(PositionVector pos, int w, int h)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				setOpen(true, pos.x() + x, pos.y() + y);
			}
		}
	}

	void CompactMaze::exploreRegion(PositionVector pos, int w, int h)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				setExplored(true, pos.x() + x, pos.y() + y);
			}
		}
	}

	direction CompactMaze::randomPossibleDirection(PositionVector pos, vector<PositionVector*>& path)
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
			path.push_back(new PositionVector(pos.x(), pos.y()));
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

	void CompactMaze::destroyRandomWallInPerimeter(PositionVector pos, int w, int h)
	{
		w /= 2; //DO NOT SIMPLIFY: w/2 needs to round down to the nearest int w;
		h /= 2; //DO NOT SIMPLIFY: h/2 needs to round down to the nearest int h;
		int numWallsInPerimeter = 2*( w + h );
		int r = rand() % numWallsInPerimeter;
		int x, y;

		if (r < 2*w)
		{
			x = 2*( r % w ) + 1;
			y = 2*h * (r/w);
		}
		else
		{
			r = r - 2*w;
			x = 2*w * (r/h);
			y = 2*(r % h) + 1;
		}

		setOpen(true, pos.x() + x, pos.y() + y);
	}

	void CompactMaze::destroyRandomWall()
	{
		int x;
		int y = rand() % height;

		if (y % 2 == 0)
		{
			x = 2 * (rand() % ((width - 1) / 2)) + 1;
			PositionVector pos(x, y);
			if (!isExplored(x, y) && getNumAdjacentWalls(pos + N) > 1 && getNumAdjacentWalls(pos + S) > 1)
			{
				setOpen(true, pos);
			}
			else
			{
				destroyRandomWall();
			}
		}
		else
		{
			x = 2 * (rand() % ((width + 1) / 2));
			PositionVector pos(x, y);
			if (!isExplored(x, y) && getNumAdjacentWalls(pos + E) > 1 && getNumAdjacentWalls(pos + W) > 1)
			{
				setOpen(true, pos);
			}
			else
			{
				destroyRandomWall();
			}
		}
	}

	int CompactMaze::getNumAdjacentWalls(PositionVector pos)
	{
		int n = 0;
		if (!isOpen(pos + N)) n++;
		if (!isOpen(pos + E)) n++;
		if (!isOpen(pos + S)) n++;
		if (!isOpen(pos + W)) n++;
		return n;
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
						if (y % 2 == 0 && x % 2 == 1)
						{
							out << "| ";
						}
						else if (y % 2 == 1 && x % 2 == 0)
						{
							out << "- ";
						}
						else
						{
							out << "+ ";
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
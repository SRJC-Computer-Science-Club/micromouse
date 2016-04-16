/*********************************\
File:			VirtualMaze.cpp
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "VirtualMaze.h"
#include <assert.h>

#ifdef __MK20DX256__ // Teensy Compile
	#include <Arduino.h>//random
#else
	#include <stdlib.h> //rand
#endif

namespace Micromouse
{
	// CONSTRUCTOR //
	VirtualMaze::VirtualMaze(int width, int height) :
		open(FlagMatrix(width, height)),
		explored(FlagMatrix(width, height)),
		width(width),
		height(height)
	{
		assert(width % 4 == 3 && height % 4 == 3);
	}


	// SET / GET FUNCTIONS //

	void VirtualMaze::setOpen(bool flag, int x, int y)
	{
		open.setFlag(flag, x, y);
	}

	void VirtualMaze::setOpen(bool flag, PositionVector pos)
	{
		setOpen(flag, pos.x(), pos.y());
	}

	void VirtualMaze::setExplored(bool flag, int x, int y)
	{
		explored.setFlag(flag, x, y);
	}

	void VirtualMaze::setExplored(bool flag, PositionVector pos)
	{ 
		setExplored(flag, pos.x(), pos.y());
	}

	bool VirtualMaze::isOpen(int x, int y) const
	{
		return open.getFlag(x, y);
	}

	bool VirtualMaze::isOpen(PositionVector pos) const
	{
		return isOpen(pos.x(), pos.y());
	}

	bool VirtualMaze::isExplored(int x, int y) const
	{
		return explored.getFlag(x, y);
	}

	bool VirtualMaze::isExplored(PositionVector pos) const
	{
		return isExplored(pos.x(), pos.y());
	}

	bool VirtualMaze::isInsideMaze(int x, int y) const
	{
		return (x >= 0) && (y >= 0) && (x < width) && (y < height);
	}

	bool VirtualMaze::isInsideMaze(PositionVector pos) const
	{
		return isInsideMaze(pos.x(), pos.y());
	}

	int VirtualMaze::getWidth() const
	{
		return width;
	}

	int VirtualMaze::getHeight() const
	{
		return height;
	}


	// GENERATION FUNCTIONS //

	void VirtualMaze::generateRandomMaze()
	{
		//Initializes the starting cell.
		setExplored(true, 0, 0);
		setOpen(true, 0, 0);

		//Create 2x2 end zone in the middle.
		openRegion(PositionVector(width / 2 - 1, height / 2 - 1), 3, 3);
		exploreRegion(PositionVector(width / 2 - 2, height / 2 - 2), 5, 5);

		//path contains every position where a random direction was picked.
		std::vector<PositionVector*> path;
		path.push_back(new PositionVector(0, 0));

		//Generates the maze
		while (!path.empty())
		{
#ifdef __MK20DX256__ // Teensy Compile
			int r = random(path.size());
#else // PC compile
			int r = rand() % path.size();
#endif

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



	void VirtualMaze::openRegion(PositionVector pos, int w, int h)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				setOpen(true, pos.x() + x, pos.y() + y);
			}
		}
	}



	void VirtualMaze::exploreRegion(PositionVector pos, int w, int h)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				setExplored(true, pos.x() + x, pos.y() + y);
			}
		}
	}



	direction VirtualMaze::randomPossibleDirection(PositionVector pos, std::vector<PositionVector*>& path)
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
#ifdef __MK20DX256__ // Teensy Compile
			int r = random(numPossibleDirections);
#else // PC compile
			int r = rand() % numPossibleDirections;
#endif
			return possibleDirections[r];
		}
	}



	void VirtualMaze::destroyRandomWallInPerimeter(PositionVector pos, int w, int h)
	{
		w /= 2; //DO NOT SIMPLIFY: w/2 needs to round down to the nearest int w;
		h /= 2; //DO NOT SIMPLIFY: h/2 needs to round down to the nearest int h;
		int numWallsInPerimeter = 2*( w + h );
#ifdef __MK20DX256__ // Teensy Compile
		int r = random(numWallsInPerimeter);
#else // PC compile
		int r = rand() % numWallsInPerimeter;
#endif
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



	void VirtualMaze::destroyRandomWall()
	{
		int x;
#ifdef __MK20DX256__ // Teensy Compile
		int y = random(height);
#else // PC compile
		int y = rand() % height;
#endif

		if (y % 2 == 0)
		{
#ifdef __MK20DX256__ // Teensy Compile
			x = 2 * (random((width - 1) / 2)) + 1;
#else // PC compile
			x = 2 * (rand() % ((width - 1) / 2)) + 1;
#endif
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
#ifdef __MK20DX256__ // Teensy Compile
			x = 2 * random((width + 1) / 2);
#else // PC compile
			x = 2 * (rand() % ((width + 1) / 2));
#endif
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



	int VirtualMaze::getNumAdjacentWalls(PositionVector pos)
	{
		int n = 0;

		if (!isOpen(pos + N)) n++;
		if (!isOpen(pos + E)) n++;
		if (!isOpen(pos + S)) n++;
		if (!isOpen(pos + W)) n++;

		return n;
	}


#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
	std::ostream& operator<<(std::ostream& out, const VirtualMaze& maze)
	{
		out << std::endl << "+ ";

		for (int x = 0; x < maze.getWidth(); x++)
		{
			out << "- ";
		}

		out << "+" << std::endl;

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

			out << "|" << std::endl;
		}

		out << "+ ";

		for (int x = 0; x < maze.getWidth(); x++)
		{
			out << "- ";
		}

		out << "+" << std::endl;

		return out;
	}
#endif
}

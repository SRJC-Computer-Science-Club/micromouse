/*********************************\
File:			CompactMaze.h
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include <ostream>
#include <vector>
#include "FlagMatrix.h"
#include "Vector.h"

using namespace std;

namespace Micromouse
{
	//A class that stores data about a maze.
	//Each cell, edge, and corner of the map can be either
	//open or closed, and either explored or unexplored.
	class CompactMaze
	{
	public:
		//Creates a maze with the given width and height.
		//width and height must each be greater than 0 and
		//must each be 1 less than a multiple of 4.
		//(3, 7, 11, 15, 19, 23, 27, 31, ...)
		CompactMaze(int width, int height);

		//Sets the open flag at the given position.
		//If the position is outside the maze, nothing happens.
		void setOpen(bool flag, int x, int y);
		void setOpen(bool flag, PositionVector pos);


		//Sets the explored flag at the given position.
		//If the position is outside the maze, nothing happens.
		void setExplored(bool flag, int x, int y);
		void setExplored(bool flag, PositionVector pos);

		//Returns the open flag at the given position.
		//If the position is outside the maze, returns false.
		bool isOpen(int x, int y) const;
		bool isOpen(PositionVector pos) const;


		//Returns the explored flag at the given position.
		//If the position is outside the maze, returns false.
		bool isExplored(int x, int y) const;
		bool isExplored(PositionVector pos) const;

		//Returns true if the given position in within the maze.
		//( 0 <= x < width and 0 <= y < height )
		bool isInsideMaze(int x, int y) const;
		bool isInsideMaze(PositionVector pos) const;

		//Returns the width of the maze.
		int getWidth() const;

		//Returns the height of the maze.
		int getHeight() const;

		//Generates a random maze, with a 2x2 empty finish area at the center.
		//The generated maze does contain loops.
		void generateRandomMaze();
	private:

		//Sets the open flags = true in the region.
		void openRegion(PositionVector pos, int w, int h);

		//Sets the explored flags = true in the region.
		void exploreRegion(PositionVector pos, int w, int h);

		direction randomPossibleDirection(PositionVector pos, vector<PositionVector*>& path);

		//Opens a random wall in the perimeter of the given region.
		void destroyRandomWallInPerimeter(PositionVector pos, int w, int h);

		//Opens a random, unexplored wall in the maze.
		//Will not open a wall if it is the only wall connected to a corner.
		//If unable to open the randomly selected wall, the function will call itself.
		void destroyRandomWall();

		//Returns the number of closed edges adjacent to the given position.
		int getNumAdjacentWalls(PositionVector pos);

		//A 2D array of flags (booleans), that denote whether or not a cell, edge, or corner is open.
		FlagMatrix open;

		//A 2D array of flags (booleans), that denote whether or not a cell, edge, or corner has been explored.
		FlagMatrix explored;

		//The dimensions of the maze.
		int width;
		int height;
	};

	//Prints out a picture of the maze for debugging.
	//Just use: log( DEBUGX ) << maze;
	ostream& operator<<(ostream& out, const CompactMaze& maze);
}

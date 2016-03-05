/*********************************\
File:			CompactMaze.h
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include "FlagMatrix.h"
#include "Vector.h"
#include <iostream>
#include <vector>

using namespace std;

namespace Micromouse
{
	class CompactMaze
	{
	public:
		CompactMaze(int width, int height);

		void setOpen(bool flag, int x, int y);
		void setOpen(bool flag, Vector::Pos pos);

		void setExplored(bool flag, int x, int y);
		void setExplored(bool flag, Vector::Pos pos);

		bool isOpen(int x, int y) const;
		bool isOpen(Vector::Pos pos) const;

		bool isExplored(int x, int y) const;
		bool isExplored(Vector::Pos pos) const;

		bool isInsideMaze(int x, int y) const;
		bool isInsideMaze(Vector::Pos pos) const;

		int getWidth() const;
		int getHeight() const;

		void generateRandomMap();
	private:
		direction randomPossibleDirection(Vector::Pos pos);

		FlagMatrix open;
		FlagMatrix explored;
		int width;
		int height;
	};

	ostream& operator<<(ostream& out, const CompactMaze& maze);
}
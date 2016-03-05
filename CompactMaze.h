/*********************************\
File:			CompactMaze.h
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include "FlagMatrix.h"
#include "Vector.h"
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

		bool isOpen(int x, int y);
		bool isOpen(Vector::Pos pos);

		bool isExplored(int x, int y);
		bool isExplored(Vector::Pos pos);

		void generateRandomMap();
	private:
		direction randomPossibleDirection(Vector::Pos pos);

		FlagMatrix open;
		FlagMatrix explored;
		int width;
		int height;
	};
}
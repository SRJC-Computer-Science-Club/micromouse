/*********************************\
File:			FlagMatrix.cpp
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "FlagMatrix.h"
#include <iostream>
#include <assert.h>

using namespace std;

namespace Micromouse
{
	FlagMatrix::FlagMatrix(int width, int height)
	{
		this->width = width;
		this->height = height;
		numDataMembers = width*height / NUM_BITS;
		if (width*height % NUM_BITS > 0) numDataMembers++;

		data = new unsigned int[numDataMembers];
		for (int i = 0; i < numDataMembers; i++)
		{
			data[i] = 0x0;
		}
	}

	FlagMatrix::~FlagMatrix()
	{
		delete[] data;
	}

	FlagMatrix::FlagMatrix(const FlagMatrix& matrix)
	{
		delete[] data;

		width, height = matrix.width, matrix.height;
		numDataMembers = matrix.numDataMembers;

		data = new unsigned int[numDataMembers];
		for (int i = 0; i < numDataMembers; i++)
		{
			data[i] = matrix.data[i];
		}
	}

	void FlagMatrix::setFlag(bool flag, int x, int y)
	{
		if ((x < width) && (y < height) && (x >= 0) && (y >= 0))
		{
			Index i = indexFromCoord(x, y);

			if (flag)
			{
				data[i.byteIndex] = data[i.byteIndex] | i.flagOffset;
			}
			else
			{
				i.flagOffset = ~i.flagOffset;
				data[i.byteIndex] = data[i.byteIndex] & i.flagOffset;
			}
		}
	}

	bool FlagMatrix::getFlag(int x, int y) const
	{
		assert((x < width) && (y < height) && (x >= 0) && (y >= 0));
		Index i = indexFromCoord(x, y);
		return (data[i.byteIndex] & i.flagOffset) > 0;
	}

	int FlagMatrix::getWidth() const
	{
		return width;
	}

	int FlagMatrix::getHeight() const
	{
		return height;
	}

	int FlagMatrix::getNumBytes() const
	{
		return numDataMembers * NUM_BITS / 8;
	}

	FlagMatrix::Index FlagMatrix::indexFromCoord(int x, int y) const
	{
		Index i;
		int flagIndex = x + y * width;
		i.byteIndex = flagIndex / NUM_BITS;
		i.flagOffset = 0x1 << (flagIndex % NUM_BITS);
		return i;
	}

	ostream& operator<<(ostream& out, const FlagMatrix& matrix)
	{
		out << endl << '+';
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			out << " -";
		}
		out << " +" << endl;
		for (int y = matrix.getHeight() - 1; y >= 0; y--)
		{
			out << "| ";
			for (int x = 0; x < matrix.getWidth(); x++)
			{
				out << matrix.getFlag(x, y) << ' ';
			}
			out << '|' << endl;
		}
		out << '+';
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			out << " -";
		}
		out << " +" << endl;
		return	out;
	}
}


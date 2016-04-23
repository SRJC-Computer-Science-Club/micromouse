/*********************************\
File:			FlagMatrix.h
Creation date:	3/4/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#pragma once
#include <ostream>

namespace Micromouse
{
	//A 2D array of flags. Each flag can be either true or false.
	//It's a compact form a data storage, because each byte represents 8 flags.
	class FlagMatrix
	{
	public:
		FlagMatrix(int width, int height); //Initializes a 2D array of flags, with the given height and width, and sets them all to false.
		~FlagMatrix();
		FlagMatrix(const FlagMatrix& matrix);

		void setFlag(bool flag, int x, int y); //Sets the flag at the given coordinates to true or false.
		bool getFlag(int x, int y) const; //Returns the value of the flag at the given coordinates.
		int getWidth() const; //Returns the width of the matrix.
		int getHeight() const; //Returns the height of the matrix.
		int getNumBytes() const; //Returns the estimated number of bytes used by the data in the matrix. (Underestimate)

	private:
		const int NUM_BITS = 32;

		struct Index
		{
			int byteIndex;
			int flagOffset;
		};

		Index indexFromCoord(int x, int y) const;

		int width, height;
		int numDataMembers;
		unsigned int* data;
	};

#ifdef __MK20DX256__ // Teensy Compile
#else
	std::ostream& operator<<(std::ostream& out, const FlagMatrix& matrix); //Printout for debugging.
#endif
}

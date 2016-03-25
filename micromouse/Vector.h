#pragma once

#include <ostream>

using namespace std;

namespace Micromouse
{
	//number of cells in maze
	const int MAZE_W = 16, MAZE_H = 16;

	//number of nodes used to represent the maze
	const int NUM_NODES_W = MAZE_W * 2 - 1 , NUM_NODES_H = MAZE_H * 2 - 1; 


	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to coordinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	// TODO: move into own namespace maybe?

	//Old enum order
	//enum direction { NW , N , NE , W , NONE , E , SW , S , SE };

	enum direction { N, NE, E, SE, S, SW, W, NW, NONE };

	// Rotate Operator: dir1 + dir2
	// Returns dir1, rotated in the direction of dir2,
	// where north is forward, east is right, south is backward, etc.
	direction operator+(const direction &dir1, const direction &dir2);
	direction operator-(const direction &dir1, const direction &dir2);

	// Increment operator (prefix)
	// dir is incremented by 1 (45 degrees to the right),
	// and then returned. NE will be incremented to NONE,
	// signifying the last direction. NONE will be incremented
	// to N.
	direction& operator++(direction& dir);

#ifdef __MK20DX256__ //this is the Teensy signature
#else
	ostream& operator<<(ostream& out, const direction& dir);
#endif

	// a position vector that represents a coordinate within the maze
	// it contains x and y integers
	// the values for x and y are bounded to 0<=x,y<NUM_NODES_W,NUM_NODES_H
	class PositionVector
	{
	public:
		PositionVector( int x , int y );
		PositionVector(const PositionVector& pos);
		~PositionVector();

		int x() const; // return x
		int y() const; // return y 
		void x( int x ); // set x, 0 <= x < NUM_NODES_W
		void y( int y ); // set y, 0 <= y < NUM_NODES_H

		PositionVector operator+(direction dir); // Returns a Pos that has been offset in the given direction.
		PositionVector operator*(int scalar); // Returns a Pos with x and y multiplied by scalar.
		bool operator==(PositionVector pos); // Returns true of the x of each position and the y of each position are equal.
		bool operator!=(PositionVector pos); // Returns true of the x of each position and the y of each position are equal.

		// static const Pos& UNDEFINED;//a Vector that represents an undefined Vector

	private:
		void validateSelf(); //ensures x and y are within bounds

		int _x , _y;
	};





	// a direction vector that represents a direction and magnitude
	// it contains a direction 'dir' and int 'mag'
	// 'dir' cant equal NONE
	// 'mag' cant be negative or equal to the size of the maze
	class DirectionVector
	{
	public:
		DirectionVector( direction dir , int mag );
		~DirectionVector();

		direction dir(); //return the direction
		int mag(); // return the magnitude
		void dir( direction dir ); // set the direction, dir != NOONE
		void mag( int mag ); // set the magnitude, 0 <= mag < NUM_NODES_W,NUM_NODES_H

	private:
		void validateSelf(); // ensures dir and mag are with bounds

		direction _dir;
		int _mag;
	};
	
}



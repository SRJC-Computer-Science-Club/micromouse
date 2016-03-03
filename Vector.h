#pragma once

namespace Micromouse
{
	//number of cells in maze
	const int MAZE_W = 16 * 2 - 1 , MAZE_H = 16 * 2 - 1; 

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

	// --Rotate Function: dir1 % dir2 --
	// Returns dir1, rotated in the direction of dir2,
	// where north is forward, east is right, south is backward, etc.
	direction operator%(const direction &dir1, const direction &dir2);
	direction& operator++(direction& dir);

	namespace Vector
	{
		// a position vector that represents a coordinate within the maze
		// it contains x and y integers
		// the values for x and y are bounded to 0<=x,y<NUM_NODES_W,NUM_NODES_H
		class Pos
		{
		public:
			Pos( int x , int y );
			~Pos();

			int x() const; // return x
			int y() const; // return y 
			void x( int x ); // set x, 0 <= x < NUM_NODES_W
			void y( int y ); // set y, 0 <= y < NUM_NODES_H

			Pos operator+(direction dir); // Returns a Pos that has been offset in the given direction.

			// static const Vector::Pos& UNDEFINED;//a Vector that represents an undefined Vector

		private:
			void validateSelf(); //ensures x and y are within bounds

			int _x , _y;
		};





		// a direction vector that represents a direction and magnitude
		// it contains a direction 'dir' and int 'mag'
		// 'dir' cant equal NONE
		// 'mag' cant be negative or equal to the size of the maze
		class Dir
		{
		public:
			Dir( direction dir , int mag );
			~Dir();

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
}



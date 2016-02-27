#pragma once

namespace Micromouse
{
	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to Vectorinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	// TODO: move into own namespace maybe?
	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };
	
	direction& operator++( direction& dir );

	namespace Vector
	{
		// a position vector that represents a coordinate within the maze
		// it contains x and y integers
		// the values for x and y are bounded to 0<=x,y<MAZE_W,MAZE_H
		class Pos
		{
		public:
			Pos( int x , int y );
			~Pos();

			int x(); // return x
			int y(); // return y 
			void x( int x ); // set x, 0<=x<MAZE_W
			void y( int y ); // set y, 0<=y<MAZE_H


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
			void mag( int mag ); // set the magnitude, 0 <= mag < maze size

		private:
			void validateSelf(); // ensures dir and mag are with bounds

			direction _dir;
			int _mag;
		};
	}
}


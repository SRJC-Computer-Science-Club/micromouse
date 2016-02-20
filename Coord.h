#pragma once

namespace Micromouse
{

	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to Coordinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	// TODO: move into own namespace maybe?
	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };


	class Coord
	{
	public:
		Coord( int x , int y );
		~Coord();

		int x();
		int y();
		void x( int x );
		void y( int y );
		

		//static const Coord& UNDEFINED;//a coord that represents an undefined coord

	private:
		int _x , _y;
	};


	direction& operator++( direction& dir );
}



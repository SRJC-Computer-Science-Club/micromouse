#include "Coord.h"

namespace Micromouse
{
	//static const Coord & UNDEFINED = Coord( 0 , -1 );


	Coord::Coord( int x , int y ) :
		_x( x ) ,
		_y( y )
	{
	}

	Coord::~Coord()
	{
	}

	int Coord::x()
	{
		return _x;
	}
	int Coord::y()
	{
		return _y;
	}
	void Coord::x( int x )
	{
		_x = x;
	}
	void Coord::y( int y )
	{
		_y = y;
	}



	direction& operator++( direction& dir )
	{ //++prefix
		if ( dir == direction::SE )
		{
			return dir = direction::NW; // rollover
		}

		int temp = dir;

		return dir = static_cast<direction> ( ++temp );
	}
}

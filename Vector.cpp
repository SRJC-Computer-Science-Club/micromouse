#include "Vector.h"
#include <assert.h>

namespace Micromouse
{
	//static const Pos & UNDEFINED = Pos( 0 , -1 );

	namespace Vector
	{
		Pos::Pos( int x , int y ) :
			_x( x ) ,
			_y( y )
		{
			validateSelf();
		}

		Pos::~Pos()
		{
		}

		int Pos::x()
		{
			return _x;
		}
		int Pos::y()
		{
			return _y;
		}
		void Pos::x( int x )
		{
			_x = x;
			validateSelf();

		}
		void Pos::y( int y )
		{
			_y = y;
			validateSelf();
		}

		void Pos::validateSelf()
		{
			assert( _x >= 0 );
			assert( _y >= 0 );

			//TODO use constants
			assert( _x < 16 );
			assert( _y < 16 );
		}




		Dir::Dir( direction dir , int mag ):
			_dir( dir ),
			_mag( mag )
		{
			validateSelf();
		}

		Dir::~Dir() {}

		direction Dir::dir()
		{
			return _dir;
		}

		int Dir::mag()
		{
			return _mag;
		}

		void Dir::dir( direction dir )
		{
			_dir = dir;
			validateSelf();
		}

		void Dir::mag( int mag )
		{
			_mag = mag;
			validateSelf();
		}

		void Dir::validateSelf()
		{
			assert( _dir != NONE );
			assert( _mag >= 0 );

			//TODO use constant
			assert( _mag < 16 );
		}


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

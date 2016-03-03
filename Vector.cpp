#include "Vector.h"
#include <assert.h>

namespace Micromouse
{
	//static const Pos & UNDEFINED = Pos( 0 , -1 );

	namespace Vector
	{
		// Pos ///////////////////////////////////////////////////

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
			assert( _x < NUM_NODES_W );
			assert( _y < NUM_NODES_H );

			// no Pos should have a position at two odd coordinates
			assert( ( _x % 2 != 1 ) && ( _y % 2 != 1 ) );
		}




		// Dir ///////////////////////////////////////////////////

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

			assert( _mag < NUM_NODES_W || _mag < NUM_NODES_H );
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

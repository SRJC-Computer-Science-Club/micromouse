#include "Vector.h"
#include <assert.h>

using namespace std;

namespace Micromouse
{
	direction operator+(const direction &dir1, const direction &dir2)
	{
		return static_cast<direction>(((int)dir1 + (int)dir2) % 8);
	}

	direction operator-(const direction &dir1, const direction &dir2)
	{
		return static_cast<direction>(((int)dir1 - (int)dir2) % 8);
	}

	direction& operator++(direction& dir)
	{ //++prefix
		return dir = static_cast<direction>(((int)dir + 1) % 9);
	}

	ostream& operator<<(ostream& out, const direction& dir)
	{
		switch (dir)
		{
		case N:  return out << "N";
		case NE: return out << "NE";
		case E:  return out << "E";
		case SE: return out << "SE";
		case S:  return out << "S";
		case SW: return out << "SW";
		case W:  return out << "W";
		case NW: return out << "NW";
		default: return out << "NONE";
		}
	}

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



		int Pos::x() const
		{
			return _x;
		}



		int Pos::y() const
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




		Pos Pos::operator+(direction dir)
		{
			int x = _x;
			int y = _y;

			if (dir == NE || dir == N || dir == NW) { y++; }
			if (dir == NE || dir == E || dir == SE) { x++; }
			if (dir == SE || dir == S || dir == SW) { y--; }
			if (dir == NW || dir == W || dir == SW) { x--; }

			return Pos(x, y);
		}


		Pos Pos::operator*(int scalar)
		{
			return Pos(_x*scalar, _y*scalar);
		}



		void Pos::validateSelf()
		{
			assert( _x >= 0 );
			assert( _y >= 0 );
			assert( _x < NUM_NODES_W );
			assert( _y < NUM_NODES_H );

			// no Pos should have a position at two odd coordinates
			assert( ( _x % 2 == 0 ) || ( _y % 2 == 0 ) );
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
}

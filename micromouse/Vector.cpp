#include "Vector.h"
#include <assert.h>

namespace Micromouse
{
	direction operator+(const direction &dir1, const direction &dir2)
	{
		return static_cast<direction>(((int)dir1 + (int)dir2) % 8);
	}

	direction operator-(const direction &dir1, const direction &dir2)
	{
		return static_cast<direction>((64 + (int)dir1 - (int)dir2) % 8);
	}

	direction& operator++(direction& dir)
	{ //++prefix
		return dir = static_cast<direction>(((int)dir + 1) % 9);
	}

#ifdef __MK20DX256__ //this is the Teensy signature
#else
	std::ostream& operator<<(std::ostream& out, const direction& dir)
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
#endif

	//static const Pos & UNDEFINED = Pos( 0 , -1 );




	// PositionVector ///////////////////////////////////////////////////

	PositionVector::PositionVector( int x , int y ) :
		_x( x ) ,
		_y( y )
	{
		validateSelf();
	}



	PositionVector::PositionVector(const PositionVector& pos)
	{
		_x = pos._x;
		_y = pos._y;

		validateSelf();
	}



	PositionVector::~PositionVector()
	{
	}



	int PositionVector::x() const
	{
		return _x;
	}



	int PositionVector::y() const
	{
		return _y;
	}



	void PositionVector::x( int x )
	{
		_x = x;
		validateSelf();

	}



	void PositionVector::y( int y )
	{
		_y = y;
		validateSelf();
	}




	PositionVector PositionVector::operator+(direction dir)
	{
		int x = _x;
		int y = _y;

		if (dir == NE || dir == N || dir == NW) { y++; }
		if (dir == NE || dir == E || dir == SE) { x++; }
		if (dir == SE || dir == S || dir == SW) { y--; }
		if (dir == NW || dir == W || dir == SW) { x--; }

		return PositionVector(x, y);
	}


	PositionVector PositionVector::operator*(int scalar)
	{
		return PositionVector(_x*scalar, _y*scalar);
	}


	bool PositionVector::operator==(PositionVector pos)
	{
		return _x == pos._x && _y == pos._y;
	}


	bool PositionVector::operator!=(PositionVector pos)
	{
		return _x != pos._x || _y != pos._y;
	}


	void PositionVector::validateSelf()
	{
		//assert( _x >= 0 );
		//assert( _y >= 0 );
		//assert( _x < NUM_NODES_W );
		//assert( _y < NUM_NODES_H );

		// no Pos should have a position at two odd coordinates
		//assert( ( _x % 2 == 0 ) || ( _y % 2 == 0 ) );
	}






	// DirectionVector ///////////////////////////////////////////////////

	DirectionVector::DirectionVector( direction dir , int mag ):
		_dir( dir ),
		_mag( mag )
	{
		validateSelf();
	}



	DirectionVector::~DirectionVector() {}



	direction DirectionVector::dir()
	{
		return _dir;
	}



	int DirectionVector::mag()
	{
		return _mag;
	}



	void DirectionVector::dir( direction dir )
	{
		_dir = dir;
		validateSelf();
	}



	void DirectionVector::mag( int mag )
	{
		_mag = mag;
		validateSelf();
	}



	void DirectionVector::validateSelf()
	{
		assert( _dir != NONE );
		assert( _mag >= 0 );

		assert( _mag < NUM_NODES_W || _mag < NUM_NODES_H );
	}
}

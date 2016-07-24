#include "Vector.h"
#include <assert.h>

namespace Micromouse
{
	const PositionVector PositionVector::START = PositionVector(0, 0);
	const PositionVector PositionVector::FINISH = PositionVector(MAZE_W - 1, MAZE_W - 1);



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

	bool isValidPosition(int x, int y)
	{
		if (x < 0 || x >= NUM_NODES_H || y < 0 || y >= NUM_NODES_H)
		{
			// false because it is outsite the maze
			return false;
		}
		else
		{
			// false if at pos with two odd coordinates, unless at cetner of maze
			return (x % 2 == 0) || (y % 2 == 0) || (x >= MAZE_W - 2 && y >= MAZE_H - 2 && x <= MAZE_W && y <= MAZE_H );
		}
	}



#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
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



	// PositionVector ///////////////////////////////////////////////////

	PositionVector::PositionVector( int x , int y ) :
		_x( x ),
		_y( y )
	{}



	PositionVector::PositionVector(const PositionVector& pos)
	{
		_x = pos._x;
		_y = pos._y;
	}



	PositionVector::~PositionVector(){}



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
	}



	void PositionVector::y( int y )
	{
		_y = y;
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

	PositionVector PositionVector::operator+(PositionVector pos)
	{
		_x += pos.x();
		_y += pos.y();
		return *this;
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



	bool PositionVector::isValidPosition()
	{
		return Micromouse::isValidPosition(_x, _y);
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

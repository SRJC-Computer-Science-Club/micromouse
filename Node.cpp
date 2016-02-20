#include "Node.h"



using namespace pathfinding;

Node::Node( coord newPos ):
	pos( newPos )
{
	int x , y;
	for ( direction dir = direction::E; dir != direction::NONE; ++dir )
	{
		//TODO make into a function
		//see Maze.cpp getNeighborNode function for explanation
		x = pos.second + dir / 3 - 1;
		y = pos.first + dir % 3 - 1;
		
		//TODO replace with constants
		if ( x < 0 || x >= 16 || y < 0 || y >= 16 )
		{
			openDirections[ dir ] = false;
		}

		//TEMP
		if ( rand() % 20 == 1)
		{
		//	openDirections[ dir ] = false;
			closed = true;
		}
	}

}

Node::~Node()
{
}

int Node::getF() const
{
	return F;
}

int Node::getG() const
{
	return G;
}

coord Node::getPos() const
{
	return pos;
}

void Node::setG( const int newG )
{
	G = newG;
}

void Node::setF( const int newF )
{
	F = newF;
}

void Node::setParent( Node * const newParent )
{
	parent = newParent;
}

bool Node::isDirectionBlocked( direction dir )
{
	return !openDirections[ dir ];
}

bool pathfinding::Node::isClosed()
{
	return closed;
}

void pathfinding::Node::close()
{
	closed = true;
}

void pathfinding::Node::open()
{
	closed = false;
}


direction pathfinding::operator++( direction& dir )
{ //++prefix
	if ( dir == direction::SE )
	{
		return dir = direction::NW; // rollover
	}
	
	int temp = dir;

	//if ( temp == 3  )
	//{
	//	return dir = static_cast<direction> ( temp + 2 );//skip over the center
	//}

	return dir = static_cast<direction> ( ++temp );
}


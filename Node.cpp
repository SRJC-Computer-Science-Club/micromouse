#include "Node.h"
#include <sstream>


namespace Micromouse
{


	// constructors ////////////////////////////////////////////////////////
	Node::Node( Coord newPos ) :
		pos( newPos )
	{
		int x , y;
		for ( direction dir = direction::E; dir != direction::NONE; ++dir )
		{
			//TODO make into a function
			//see Maze.cpp getNeighborNode function for explanation
			x = pos.x() + dir % 3 - 1;
			y = pos.y() + dir / 3 - 1;

			//TODO replace with constants
			if ( x < 0 || x >= 16 || y < 0 || y >= 16 )
			{
				openDirections[ dir ] = false;
			}
		}

		// TEMP randomly closes nodes
		if ( rand() % 10 == 1 )
		{
			closed = true;
		}

	}

	Node::~Node()
	{
	}





	// getters //////////////////////////////////////////////////////
	int Node::getF() const
	{
		return F;
	}

	int Node::getG() const
	{
		return G;
	}

	Coord Node::getPos() const
	{
		return pos;
	}

	Node * Node::getParent()
	{
		return parent;
	}

	bool Node::isDirectionBlocked( direction dir )
	{
		return !openDirections[ dir ];
	}

	bool Micromouse::Node::isClosed()
	{
		return closed;
	}






	//setters /////////////////////////////////////////////////////////////
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




	void Micromouse::Node::close()
	{
		closed = true;
	}

	void Micromouse::Node::open()
	{
		closed = false;
	}
}








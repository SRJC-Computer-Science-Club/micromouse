#include "Node.h"
#include <sstream>


namespace Micromouse
{


	// constructors ////////////////////////////////////////////////////////
	Node::Node( Vector::Pos newPos ) :
		pos( newPos )
	{
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

	Vector::Pos Node::getPos() const
	{
		return pos;
	}

	Node * Node::getParent() const
	{
		return parent;
	}


	direction Node::getDir() const
	{
		return direction();
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

	void Node::setDir( direction dir )
	{
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








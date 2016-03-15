#include "Node.h"
#include <sstream>


namespace Micromouse
{


	// constructors ////////////////////////////////////////////////////////
	Node::Node( PositionVector newPos ) :
		pos( newPos )
	{
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

	PositionVector Node::getPos() const
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








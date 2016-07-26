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
		return dir;
	}

	bool Micromouse::Node::isExplored() const
	{
		return explored;
	}

	bool Micromouse::Node::isClosed() const
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

	void Node::setDir( direction newDir )
	{
		dir = newDir;
	}




	void Micromouse::Node::setExplored()
	{
		explored = true;
	}


	void Micromouse::Node::close()
	{
		closed = true;
	}



	void Micromouse::Node::open()
	{
		closed = false;
	}






	void Node::reset()
	{
		setParent(nullptr);
		setDir(NONE);
		setF(INF);
		setG(INF);
		open();
	}
}








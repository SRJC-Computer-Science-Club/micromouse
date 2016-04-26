#pragma once
#include "Vector.h"

const int INF = 65000;


namespace Micromouse
{
	class Node
	{
	public:
		Node( PositionVector newPos );
		~Node();

		//getters
		int getF() const;
		int getG() const;
		PositionVector getPos() const;
		Node* getParent() const;
		direction getDir() const;

		//setters
		void setG( const int newG );
		void setF( const int newF );
		void setParent( Node * const newParent );
		void setDir( direction newDir );
		
		bool isClosed();
		void close();
		void open();

		void reset();

	private:
		int G = INF; //movement cost
		int F = INF; //movement + hueristic cost
		Node* parent = nullptr; // the parent node used for pathfinding
		direction dir; // the direction from the parent node to self

		PositionVector pos;

		bool closed = false;
	};
}

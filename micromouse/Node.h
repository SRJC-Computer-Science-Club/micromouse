#pragma once
#include "Drawable.h"
#include "Vector.h"

const int INF = 65000;


namespace Micromouse
{

#ifdef SFML_GRAPHICS_HPP
	const int NODE_W = 20 , NODE_H = 20;
#endif



#ifdef SFML_GRAPHICS_HPP
	class Node : public Drawable
#else
	class Node
#endif
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
		
		bool isExplored() const;
		void setExplored();

		bool isClosed() const;
		void close();
		void open();

		void reset();

#ifdef SFML_GRAPHICS_HPP
		void draw();
#endif


	private:
		int G = INF; //movement cost
		int F = INF; //movement + hueristic cost
		Node* parent = nullptr; // the parent node used for pathfinding
		direction dir; // the direction from the parent node to self

		PositionVector pos;

		bool explored = false;
		bool closed = false;
	};
}
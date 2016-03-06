#pragma once
#include "Drawable.h"
#include "Vector.h"

const int INF = 65000;


namespace Micromouse
{
#ifdef SFML_GRAPHICS_HPP
	const int NODE_W = 24 , NODE_H = 24;
#endif



#ifdef SFML_GRAPHICS_HPP
	class Node : public Drawable
#else
	class Node
#endif
	{
	public:
		Node( Vector::Pos newPos );
		~Node();

		//getters
		int getF() const;
		int getG() const;
		Vector::Pos getPos() const;
		Node* getParent() const;
		direction getDir() const;

		//setters
		void setG( const int newG );
		void setF( const int newF );
		void setParent( Node * const newParent );
		void setDir( direction dir );
		
		bool isClosed();
		void close();
		void open();

#ifdef SFML_GRAPHICS_HPP
		void draw();
#endif
	private:
		int G = INF; //movement cost
		int F = INF; //movement + hueristic cost
		Node* parent = nullptr; // the parent node used for pathfinding
		direction dir; // the direction from the parent node to self

		Vector::Pos pos;

		bool closed = false;


	};
}
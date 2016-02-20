#pragma once
#include "Coord.h"

const int INF = 65000;


namespace Micromouse
{

#ifdef SFML_GRAPHICS_HPP
	const int NODE_W = 48 , NODE_H = 48;
#endif



#ifdef SFML_GRAPHICS_HPP
	class Node : public Drawable
#else
	class Node
#endif
	{
	public:
		Node( Coord newPos );
		~Node();

		//getters
		int getF() const;
		int getG() const;
		Coord getPos() const;
		Node* getParent();

		//setters
		void setG( const int newG );
		void setF( const int newF );
		void setParent( Node * const newParent );
		
		bool isDirectionBlocked( direction dir );
		bool isClosed();
		void close();
		void open();

#ifdef SFML_GRAPHICS_HPP
		void draw();
#endif

	private:
		bool openDirections[ 8 ] = { true , true , true , true , true , true , true , true };
		int G = INF; //movement cost
		int F = INF; //movement + hueristic cost
		Node* parent = nullptr;
		Coord pos;

		bool closed = false;


	};
}

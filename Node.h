#pragma once
#include <utility> //pair

const int INF = 65000;

typedef std::pair< int , int > coord;


namespace pathfinding
{
	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to coordinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };


	class Node
	{
	public:
		Node( coord newPos );
		~Node();

		int getF() const;
		int getG() const;
		coord getPos() const;

		void setG( const int newG );
		void setF( const int newF );
		void setParent( Node * const newParent );
		
		bool isDirectionBlocked( direction dir );
		bool isClosed();
		void close();
		void open();

	private:
		bool openDirections[ 8 ] = { true , true , true , true , true , true , true , true };
		int G = INF; //movement cost
		int F; //movement + hueristic cost
		Node* parent;
		coord pos;

		bool closed = false;


	};

	direction operator++( direction& dir );
}

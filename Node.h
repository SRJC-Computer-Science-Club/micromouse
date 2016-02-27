#pragma once
#include "Vector.h"

const int INF = 65000;


namespace Micromouse
{

	class Node
	{
	public:
		Node( Vector::Pos newPos );
		~Node();

		//getters
		int getF() const;
		int getG() const;
		Vector::Pos getPos() const;
		Node* getParent();

		//setters
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
		int F = INF; //movement + hueristic cost
		Node* parent = nullptr;
		Vector::Pos pos;

		bool closed = false;


	};
}

#pragma once
#include "Node.h"
#include "Vector.h"

namespace Micromouse
{
	class Maze
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Vectors to utilized by the motion controller
		int findPath( Vector::Pos start , Vector::Pos end );
		int findPath( const Node * const start , const Node * const end );



	private:
		// returns a pointer to the node in the direction 'dir' from the given Vector::Pos 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( Vector::Pos pos , direction dir ); 


		// populates 'maze' with Nodes
		void initNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ NUM_NODES_W ][ NUM_NODES_H ];



	};
}
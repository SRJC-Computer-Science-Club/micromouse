#pragma once
#include "Node.h"
#include "Coord.h"

namespace Micromouse
{
	const int MAZE_W = 16 , MAZE_H = 16;


	class Maze
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Coords to utilized by the motion controller
		int findPath( Coord start , Coord end );
		int findPath( const Node * const start , const Node * const end );



	private:
		// returns a pointer to the node in the direction 'dir' from the given Coord 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( Coord pos , direction dir ); 


		// populates 'maze' with Nodes
		void initNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ MAZE_W ][ MAZE_H ];



	};
}
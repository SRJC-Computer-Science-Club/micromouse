#pragma once
#include "Node.h"
#include "Vector.h"

namespace Micromouse
{
	const int MAZE_W = 16 , MAZE_H = 16;


	class Maze
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Vectors to utilized by the motion controller
		int findPath( Vector::Pos start , Vector::Pos end );
		int findPath( const Node * const start , const Node * const end );

		// adds a Node to the Maze
		// 'pos' is the position of the new Node being created
		void addNode( Vector::Pos newPos );

	private:
		// returns a pointer to the node in the direction 'dir' from the given Vector::Pos 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( Vector::Pos pos , direction dir ); 


		// populates 'maze' with Nodes
		void initNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ MAZE_W ][ MAZE_H ];



	};
}
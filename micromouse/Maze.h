#pragma once
#include "Node.h"
#include "Vector.h"
#include "Path.h"


namespace Micromouse
{
	class Maze
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Vectors to utilized by the motion controller
		Path * findPath( Vector::Pos start , Vector::Pos end );
		Path * findPath( const Node * const start , const Node * const end );

		// returns a Node from the maze
		// 'pos' is the position of the Node being returned
		Node* getNode( Vector::Pos pos );

		// adds a Node to the Maze
		// 'pos' is the position of the new Node being created
		void addNode( Vector::Pos newPos );

		// returns a pointer to the node in the direction 'dir' from the given Vector::Pos 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( Vector::Pos pos , direction dir );

	private:

		// creates a Path object after findPath has been called
		// 'node' is the finish node in the path
		// the path is created by working backwards from end node to start node
		Path* createPath( const Node* node );


		// populates 'maze' with Nodes
		void initNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ NUM_NODES_W ][ NUM_NODES_H ];



	};
}
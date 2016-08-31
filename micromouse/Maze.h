#pragma once
#include "Node.h"
#include "Vector.h"
#include "Path.h"
#include "FlagMatrix.h"

#include <vector>
#include <utility>//pair


namespace Micromouse
{
	typedef std::pair<const Node*, const Node*> NodePair;
	typedef std::vector<NodePair> NodePairList;

	class Maze
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Vectors to utilized by the motion controller
		Path * findPath( PositionVector start , PositionVector end , bool isMapping = false , NodePairList* passageNodes = nullptr );

		// returns a Node from the maze
		// 'pos' is the position of the Node being returned
		Node* getNode(PositionVector pos) const;

		// adds a Node to the Maze
		// 'pos' is the position of the new Node being created
		void addNode( PositionVector pos );

		// removes a Node from the Maze
		// 'pos' is the position of the Node being removed
		void removeNode(PositionVector pos);

		// returns a pointer to the node in the direction 'dir' from the given Pos 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( PositionVector pos , direction dir );


		//Sets the explored flag at the given position.
		//If the position is outside the maze, nothing happens.
		void setExplored( PositionVector pos );


		////Returns the explored flag at the given position.
		////If the position is outside the maze, returns false.
		//bool isExplored(int x, int y) const;
		bool isExplored(PositionVector pos) const;


		// Once the opening to the cneter has been found the other
		// nodes that form the wall around the center can be removed
		void removeExcessFinshNodes();

		void printToSerial() const;

	private:

		// creates a Path object after findPath has been called
		// 'node' is the finish node in the path
		// the path is created by working backwards from end node to start node
		Path* createPath( const Node* node , bool isMapping = false , NodePairList* passageNodes = nullptr );

		// populates 'maze' with Nodes
		void initNodes();

		// returns the Nodes in maze to their initial sates
		void resetNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ NUM_NODES_W ][ NUM_NODES_H ];

	};
}
#include <vector>
#include <algorithm>
#include <math.h>
#include "Maze.h"

namespace Micromouse
{
	// constructors //////////////////////////////////////////////////

	Maze::Maze()
	{
		initNodes();
	}


	Maze::~Maze()
	{
	}




	// this is to allow the sorting of the vector of Nodes
	// sorts in descending order
	bool nodeComparator( const Node* lhs , const Node* rhs )
	{
		return lhs->getF() > rhs->getF();
	}



	Path * Maze::findPath( Vector::Pos start , Vector::Pos end )
	{
		std::vector< Node* > openNodes;

		// assume 1/2 of the maze will need to be searched on average;
		// this prevents too many resizes, idk if this is optimal I was just estimating
		openNodes.reserve( static_cast< int >( NUM_NODES_W * NUM_NODES_H * 0.5f ) );


		openNodes.push_back( maze[ start.x() ][ start.y() ] );// the start node is added to openNodes
		maze[ start.x() ][ start.y() ]->setG( 0 ); // initialize the movement cost to 0 for the first node

		Node* currentNode;
		Node* neighborNode;
		int tentative_G;

		while ( !openNodes.empty() ) //while openNodes is not empty
		{
			std::sort( openNodes.begin() , openNodes.end() , nodeComparator ); //sort in descending order by F value
			currentNode = openNodes.back(); //get node will lowest F value

			if ( currentNode == maze[ end.x() ][ end.y() ] ) // if we are at the end node then we are done!
			{
				return createPath( currentNode ); // create a Path object for motion control to utilize
			}

			openNodes.pop_back();
			currentNode->close();

			for ( direction dir = direction::E; dir != direction::NONE; ++dir )
				//loop through neighbor nodes
			{
				neighborNode = getNeighborNode( currentNode->getPos() , dir );

				if ( neighborNode == nullptr )
				{
					continue; // there is no neighbor node in this direction
				}

				if ( neighborNode->isClosed() ) //if neighborNode in closedNodes
				{
					continue; // Ignore the neighbor which is already evaluated
				}


				//TODO turn this into a function
				tentative_G = currentNode->getG();
				tentative_G += ( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE ) ? 14 : 10; //if moved diagnal add 14, else moved straight add 10


				if ( std::find( openNodes.begin() , openNodes.end() , neighborNode )
					== openNodes.end() )
					//if neighborNode not in openNodes
				{
					openNodes.push_back( neighborNode );
				}
				// neighborNode is already in openNodes
				else if ( tentative_G >= neighborNode->getG() )
					// if new path to neighborNode is worse than previous
				{
					continue; //this is not a better path
				}

				//if we made it to this point then
				//this path is the best so far
				neighborNode->setParent( currentNode );
				neighborNode->setDir( dir );
				neighborNode->setG( tentative_G );
				neighborNode->setF( tentative_G + 0 /*TODO calculate Hueristic here*/ );
			}
		}

		// no path was found
		// this should never happen in real maze
		// TODO throw error if this is reached in real testing
		return nullptr;
	}



	// an overload of  findPath that takes nodes instead of Vectors
	// might be useful
	Path * Maze::findPath( const Node * const start , const Node * const end )
	{
		return findPath( start->getPos() , end->getPos() );
	}

	// Retruns the Node at the given position.
	Node* Maze::getNode( Vector::Pos pos )
	{
		return maze[ pos.x ][ pos.y ];
	}



	// adds a new node to the maze at the given position
	void Maze::addNode( Vector::Pos pos )
	{
		maze[ pos.x() ][ pos.y() ] = new Node( pos );
	}





	// returns a pointer to the neighbor node at direction dir from pos
	Node * Maze::getNeighborNode( Vector::Pos pos , direction dir )
	{
		int x = pos.x() + dir % 3 - 1;
		int y = pos.y() + dir / 3 - 1;

		if ( x >= 0 && x < NUM_NODES_W && y >= 0 && y < NUM_NODES_H )
		{
			return maze[ x ][ y ];
		}
		/*       x
			 -1  0  1
			----------
		 -1| NW| N |NE|
		   |---+---+--|
		y 0| W |   | E|
		   |---+---+--|
		  1| SW| s  SE|
			----------
		*/

		return nullptr;
	}





	Path * Micromouse::Maze::createPath( const Node * node )
	{
		Path* path = new Path;
		direction travelDir = node->getDir();
		int mag = 1;

		// while there is more to the path to traverse
		while ( node != nullptr )
		{
			//if we are at the beginning of the path or if the path is not straight
			if ( node->getParent() == nullptr || node->getParent()->getDir() != travelDir )
			{
				// add a step to the path to define the direction and distance need to travel
				path->addStep( Vector::Dir( travelDir , mag ) );

				travelDir = node->getParent()->getDir();
				mag = 0;
			}
			//else the path is straight so no need for a step

			node = node->getParent();
			mag++;
		}

		return path;
	}




	// populates the maze with Nodes
	void Maze::initNodes()
	{
		for ( int x = 0; x < NUM_NODES_W; x++ )
		{
			for ( int y = 0; y < NUM_NODES_H; y++ )
			{
				maze[ x ][ y ] = nullptr;
			}
		}
	}
}
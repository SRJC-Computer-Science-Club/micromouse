#include <vector>
#include <algorithm>
#include <math.h>
#include "Maze.h"

using namespace Micromouse;

// constructors //////////////////////////////////////////////////

Maze::Maze()
{
	initNodes();
}


Maze::~Maze()
{
}


// this is to allow the sorting of the vecotr of Nodes
// sorts in descending order
bool nodeComparator( const Node* lhs , const Node* rhs )
{
	return lhs->getF() > rhs->getF();
}



int Maze::findPath( Coord start , Coord end )
{
	std::vector< Node* > openNodes;

	// assume 3/4 of the maze will need to be searched on average;
	// this prevents too many resizes, idk if this is optimal I was just estimating
	openNodes.reserve( static_cast< int >( MAZE_W * MAZE_H * 0.75 ) );

	openNodes.push_back( maze[ start.x() ][ start.y() ] );// the start node is add to openNodes
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
#ifdef SFML_GRAPHICS_HPP
			Node* temp = currentNode;
			while ( temp->getParent() != nullptr ) // draw the path pack to the start node
			{
				drawLine( temp->getPos() , temp->getParent()->getPos() );
				temp = temp->getParent();
			}
#endif

			// TODO: this should return a list of coords for the motion control to utilize
			return currentNode->getF(); // return the cost of the trip
		}

		openNodes.pop_back();
		currentNode->close();

		for ( direction dir = direction::E; dir != direction::NONE; ++dir )
			//loop through neighbor nodes
		{
			// TODO get diagonals working
			//Diagonals are broken right now so this will skip over them
			if ( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE )
			{
				continue; // skip checking diagonals
			}

			// BUG TODO see why this returns invalid objects sometimes
			// TODO incorporate this into getNeighborNode
			if ( currentNode->isDirectionBlocked( dir ) )
			{
				continue; //neighbor node not reachable from current node
			}

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
			neighborNode->setG( tentative_G );
			neighborNode->setF( tentative_G + 0 /*TODO calculate Hueristic here*/ );
		}
	}

	// no path was found
	// this should never happen in real maze
	return -1;
}



// an overload of  findPath that takes nodes instead of coords
// might be useful
int Maze::findPath( const Node * const start , const Node * const end )
{
	return findPath( start->getPos() , end->getPos() );
}




// returns a pointer to the neighbor node at direction dir from pos
Node * Maze::getNeighborNode( Coord pos , direction dir )
{
	int x = pos.x() + dir % 3 - 1;
	int y = pos.y() + dir / 3 - 1;

	if ( x >= 0 && x < MAZE_W && y >= 0 && y < MAZE_H )
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



// populates the maze with Nodes
void Maze::initNodes()
{
	for ( int x = 0; x < MAZE_W; x++ )
	{
		for ( int y = 0; y < MAZE_H; y++ )
		{
			maze[ x ][ y ] = new Node( Coord( x , y ) );
		}
	}
}








#ifdef SFML_GRAPHICS_HPP
void Micromouse::Maze::drawLine( Coord begin , Coord end )
{
	sf::Vertex line[ 2 ];
	sf::Color color = sf::Color( 200 , 80 , 30 );
	line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * begin.x() + 40.0f , NODE_H * begin.y() + 40.0f ) , color );
	line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * end.x() + 40.0f , NODE_H * end.y() + 40.0f ) , color );
	renderWindow.draw( line , 2 , sf::Lines );
}






void Maze::draw()
{
	for ( int x = 0; x < MAZE_W; x++ )
	{
		for ( int y = 0; y < MAZE_H; y++ )
		{
			maze[ x ][ y ]->draw();
		}
	}
}
#endif



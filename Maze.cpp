#include <vector>
#include <algorithm>
#include "Maze.h"
#include "Node.h"
#include <math.h>

using namespace Micromouse;

#ifdef SFML_GRAPHICS_HPP
//sf::RenderWindow renderWindow( sf::VideoMode( 680 , 600 ) , "MicroMouse Sim" );
//sf::Event event;
//
sf::Vertex line[] =
{
	sf::Vertex( sf::Vector2f( 0, 16 ),  sf::Color( 100 , 250 , 50 ) ),
	sf::Vertex( sf::Vector2f( 512, 16 ),  sf::Color( 100 , 250 , 50 ) )
};
#endif




Maze::Maze()
{
	initNodes();
}



Maze::~Maze()
{
}


bool nodeComparator( const Node* lhs , const Node* rhs )
{
	return lhs->getF() > rhs->getF();
}

int Maze::findPath( coord start , coord end )
{
#ifdef SFML_GRAPHICS_HPP




#endif

	std::vector< Node* > openNodes;

	openNodes.reserve( static_cast< int >( MAZE_W * MAZE_H * 0.75 ) ); //assume 3/4 of the maze will need to be searched on average;

	openNodes.push_back( maze[ start.second ][ start.first ] );

	Node* currentNode;
	Node* neighborNode;
	int tentative_G;

	while ( !openNodes.empty() ) //while openNodes is not empty
	{
		std::sort( openNodes.begin() , openNodes.end() , nodeComparator ); //sort in descending order by F value
		currentNode = openNodes.back();

		if ( currentNode == maze[ end.second ][ end.first ] )
		{
			Node* temp = currentNode;
			while ( temp->getParent() != nullptr )
			{
				drawLine( temp->getPos() , temp->getParent()->getPos() );
				temp = temp->getParent();
			}

			//drawLine( start , end );
			return currentNode->getF();
		}

		openNodes.pop_back();
		currentNode->close();

		for ( direction dir = direction::E; dir != direction::NONE; ++dir )
			//loop through neighbor nodes
		{

			if ( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE )
			{
				continue;
			}
			// TODO see why this returns invalid objects
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


			//TODO make a function that returns the traval cost
			tentative_G = currentNode->getG();
			tentative_G +=	( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE ) ? 14 : 10; //if moved diagnal add 14, else moved straight add 10


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
			neighborNode->setF( tentative_G + 5 * ( abs( currentNode->getPos().first - end.first ) + abs( currentNode->getPos().second - end.second ) )
				/*TODO calculate Hueristic here*/  );
		}
	}

	// no path was found
	return 0;
}

int Maze::findPath( const Node * const start , const Node * const end )
{
	return findPath( start->getPos() , end->getPos() );
}


// returns a pointer to trhe neighbor node at direction dir from pos
// does not do bound checking and assumes that the neighbor node pointed at exists
Node * Maze::getNeighborNode( coord pos , direction dir )
{
	int x = pos.first + dir % 3 - 1;
	int y = pos.second + dir / 3 - 1;
	//return maze[ ypos + offset][ xpos + offset ]
	if ( x >= 0 && x < MAZE_W && y >= 0 && y < MAZE_H )
	{
		return maze[ y ][ x ];
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

void Maze::initNodes()
{
	for ( int i = 0; i < MAZE_W; i++ )
	{
		for ( int j = 0; j < MAZE_H; j++ )
		{
			maze[ j ][ i ] = new Node( coord( i , j ) );
		}
	}
}

void Micromouse::Maze::drawLine( coord begin , coord end )
{
	sf::Vertex line[ 2 ];
	sf::Color color = sf::Color( 200 , 80 , 30 );
	line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * begin.first + 40.0f , NODE_H * begin.second + 40.0f ) , color );
	line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * end.first + 40.0f , NODE_H * end.second + 40.0f ) , color );
	renderWindow.draw( line , 2 , sf::Lines );
}





#ifdef SFML_GRAPHICS_HPP

void Maze::draw()
{
	for ( int i = 0; i < MAZE_W; i++ )
	{
		for ( int j = 0; j < MAZE_H; j++ )
		{
			maze[ j ][ i ]->draw();
		}
	}
}
#endif




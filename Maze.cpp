#include <vector>
#include <algorithm>
#include "Maze.h"


using namespace pathfinding;

#ifdef SFML_GRAPHICS_HPP
//sf::RenderWindow renderWindow( sf::VideoMode( 680 , 600 ) , "MicroMouse Sim" );
//sf::Event event;
//
sf::Vertex line[] =
{
	sf::Vertex( sf::Vector2f( 0, 16 ),  sf::Color( 100 , 250 , 50 ) ),
	sf::Vertex( sf::Vector2f( 512, 16 ),  sf::Color( 100 , 250 , 50 ) )
};


sf::Font font;


Maze::Maze( sf::RenderWindow& rw ) :
	rw( rw )
{
	for ( int i = 0; i < MAZE_W; i++ )
	{
		for ( int j = 0; j < MAZE_H; j++ )
		{
			maze[ j ][ i ] = new Node( coord( i , j ) );
		}
	}


	if ( !font.loadFromFile( "font.ttf" ) )
	{
		// error...
		throw;
	}
}

#else

Maze::Maze()
{
}
#endif

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
	sf::RectangleShape rect;
	for ( int i = 0; i < MAZE_H; i++ )
	{
		for ( int j = 0; j < MAZE_W; j++ )
		{


			//rect = sf::RectangleShape( sf::Vector2f( NODE_W , NODE_H ) );
			//rect.setPosition( sf::Vector2f( NODE_W * j + 16 , NODE_H * i + 16 ) );
			//rect.setOutlineThickness( 1 );
			//rect.setFillColor( sf::Color::Black );
			drawNode( i , j );
			//sf::sleep( sf::microseconds( 1000 ) );

		}
	}
	rw.display();

	//rw.draw( line , 2 , sf::Lines );
	//rw.display();

#endif

	return 0;
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
			currentNode->getF();;
		}

		openNodes.pop_back();
		currentNode->close();

		for ( direction dir = direction::E; dir != direction::NONE; ++dir )
			//loop through neighbor nodes
		{
			if ( currentNode->isDirectionBlocked( dir ) )
			{
				continue; //neighbor node not reachable from current node
			}

			neighborNode = getNeighborNode( currentNode->getPos() , dir );


			if ( neighborNode->isClosed() ) //if neighborNode in closedNodes
			{
				continue; // Ignore the neighbor which is already evaluated
			}


			//TODO make a function that returns the traval cost
			tentative_G = currentNode->getG() +
				( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE ) ? 14 : 10; //if moved diagnal add 14, else moved straight add 10


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
			neighborNode->setF( tentative_G + /*TODO calculate Hueristic here*/ 0 );
		}
	}

	// no path was found
	return 0;
}

int Maze::findPath( const Node & start , const Node & end )
{
	return findPath( start.getPos() , end.getPos() );
}


// returns a pointer to trhe neighbor node at direction dir from pos
// does not do bound checking and assumes that the neighbor node pointed at exists
Node * Maze::getNeighborNode( coord pos , direction dir )
{
	//return maze[ ypos + offset][ xpos + offset ]
	return maze[ pos.second + dir / 3 - 1 ][ pos.first + dir % 3 - 1 ];
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





#ifdef SFML_GRAPHICS_HPP

void pathfinding::Maze::drawNode( int i , int j )
{
	for ( direction dir = direction::E; dir != direction::NONE; ++dir )
	{
		sf::Color color;
		if ( maze[ i ][ j ]->isClosed() )
		{
			color = maze[ i ][ j ]->directionIsBlocked( dir ) ? sf::Color::Color( 200 , 30 , 30 ) : sf::Color( 45 , 0 , 0 );
		}
		else
		{
			color = maze[ i ][ j ]->directionIsBlocked( dir ) ? sf::Color::Color( 200 , 200 , 200 ) : sf::Color( 40 , 40 , 40 );
		}
		sf::Vertex line[ 2 ];

		switch ( dir )
		{
		case pathfinding::N:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * i + 16 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 14 , NODE_H * i + 16 ) , color );

			break;
		case pathfinding::W:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * i + 16 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * ( i + 1 ) + 15 ) , color );

			break;
		case pathfinding::E:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 14 , NODE_H * i + 16 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 14 , NODE_H * ( i + 1 ) + 14 ) , color );

			break;
		case pathfinding::S:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * ( i + 1 ) + 14 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 14 , NODE_H * ( i + 1 ) + 14 ) , color );

			break;
		case pathfinding::NW:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * i + 25 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 25 , NODE_H * i + 16 ) , color );

			break;
		case pathfinding::NE:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 13 , NODE_H * i + 25 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 4 , NODE_H * i + 16 ) , color );

			break;
		case pathfinding::SW:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 16 , NODE_H * ( i + 1 ) + 6 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * j + 24 , NODE_H * ( i + 1 ) + 14 ) , color );

			break;
		case pathfinding::SE:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 14 , NODE_H * ( i + 1 ) + 5 ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( j + 1 ) + 5 , NODE_H * ( i + 1 ) + 14 ) , color );

			break;
		default:
			break;
		}
		sf::Text text;
		text.setFont( font );
		text.setPosition( sf::Vector2f( NODE_W * j + 18 , NODE_H * i + 25 ) );
		text.setString( "G:" );
		text.setCharacterSize( 7 );
		rw.draw( text );
		rw.draw( line , 2 , sf::Lines );
	}
}

#endif




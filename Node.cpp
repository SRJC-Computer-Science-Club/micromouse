#include "Node.h"
#include <sstream>


using namespace Micromouse;

Node::Node( coord newPos ):
	pos( newPos )
{
	int x , y;
	for ( direction dir = direction::E; dir != direction::NONE; ++dir )
	{
		//TODO make into a function
		//see Maze.cpp getNeighborNode function for explanation
		x = pos.first + dir / 3 - 1;
		y = pos.second + dir % 3 - 1;
		
		//TODO replace with constants
		if ( x < 0 || x >= 16 || y < 0 || y >= 16 )
		{
			openDirections[ dir ] = false;
		}

		// TEMP randomly closes 1 in 20 nodes
		if ( rand() % 20 == 1)
		{
			//openDirections[ dir ] = false;
			closed = true;
		}
	}

}

Node::~Node()
{
}

int Node::getF() const
{
	return F;
}

int Node::getG() const
{
	return G;
}

coord Node::getPos() const
{
	return pos;
}

Node * Micromouse::Node::getParent()
{
	return parent;
}

void Node::setG( const int newG )
{
	G = newG;
}

void Node::setF( const int newF )
{
	F = newF;
}

void Node::setParent( Node * const newParent )
{
	parent = newParent;
}

bool Node::isDirectionBlocked( direction dir )
{
	return !openDirections[ dir ];
}

bool Micromouse::Node::isClosed()
{
	return closed;
}

void Micromouse::Node::close()
{
	closed = true;
}

void Micromouse::Node::open()
{
	closed = false;
}

void Micromouse::Node::draw()
{
	// TODO make this function not so gigantic
	for ( direction dir = direction::E; dir != direction::NONE; ++dir )
	{
		sf::Color color;
		if ( isClosed() )
		{
			color = isDirectionBlocked( dir ) ? sf::Color::Color( 250 , 30 , 30 ) : sf::Color( 200 , 0 , 0 );
		}
		else
		{
			color = isDirectionBlocked( dir ) ? sf::Color::Color( 250 , 250 , 250 ) : sf::Color( 50 , 50 , 50 );
		}
		sf::Vertex line[ 2 ];

		switch ( dir )
		{
		case Micromouse::N:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * pos.second + 16.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 14.0f , NODE_H * pos.second + 16.0f ) , color );

			break;
		case Micromouse::W:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * pos.second + 16.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * ( pos.second + 1 ) + 15.0f ) , color );

			break;
		case Micromouse::E:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 14.0f , NODE_H * pos.second + 16.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 14.0f , NODE_H * ( pos.second + 1 ) + 14.0f ) , color );

			break;
		case Micromouse::S:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * ( pos.second + 1 ) + 14.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 14.0f , NODE_H * ( pos.second + 1 ) + 14.0f ) , color );

			break;
		case Micromouse::NW:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * pos.second + 25.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 25.0f , NODE_H * pos.second + 16.0f ) , color );

			break;
		case Micromouse::NE:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 13.0f , NODE_H * pos.second + 25.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 4.0f , NODE_H * pos.second + 16.0f ) , color );

			break;
		case Micromouse::SW:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 16.0f , NODE_H * ( pos.second + 1 ) + 6.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.first + 24.0f , NODE_H * ( pos.second + 1 ) + 14.0f ) , color );

			break;
		case Micromouse::SE:

			line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 14.0f , NODE_H * ( pos.second + 1 ) + 5.0f ) , color );
			line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.first + 1 ) + 5.0f , NODE_H * ( pos.second + 1 ) + 14.0f ) , color );

			break;
		default:
			break;
		}
		sf::Text text;
		text.setFont( font );
		text.setPosition( sf::Vector2f( NODE_W * pos.second + 16.0f , NODE_H * pos.first + 25.0f ) );
		std::ostringstream ss;
		ss << pos.first << ", " << pos.second;
		text.setString( ss.str() );
		text.setCharacterSize( 7 );
		renderWindow.draw( text );
		renderWindow.draw( line , 2 , sf::Lines );
	}
}


direction Micromouse::operator++( direction& dir )
{ //++prefix
	if ( dir == direction::SE )
	{
		return dir = direction::NW; // rollover
	}
	
	int temp = dir;

	//if ( temp == 3  )
	//{
	//	return dir = static_cast<direction> ( temp + 2 );//skip over the center
	//}

	return dir = static_cast<direction> ( ++temp );
}







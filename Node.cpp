#include "Node.h"
#include <sstream>


namespace Micromouse
{


	// constructors ////////////////////////////////////////////////////////
	Node::Node( Coord newPos ) :
		pos( newPos )
	{
		int x , y;
		for ( direction dir = direction::E; dir != direction::NONE; ++dir )
		{
			//TODO make into a function
			//see Maze.cpp getNeighborNode function for explanation
			x = pos.x() + dir % 3 - 1;
			y = pos.y() + dir / 3 - 1;

			//TODO replace with constants
			if ( x < 0 || x >= 16 || y < 0 || y >= 16 )
			{
				openDirections[ dir ] = false;
			}
		}

		// TEMP randomly closes nodes
		if ( rand() % 10 == 1 )
		{
			closed = true;
		}

	}

	Node::~Node()
	{
	}





	// getters //////////////////////////////////////////////////////
	int Node::getF() const
	{
		return F;
	}

	int Node::getG() const
	{
		return G;
	}

	Coord Node::getPos() const
	{
		return pos;
	}

	Node * Node::getParent()
	{
		return parent;
	}

	bool Node::isDirectionBlocked( direction dir )
	{
		return !openDirections[ dir ];
	}

	bool Micromouse::Node::isClosed()
	{
		return closed;
	}






	//setters /////////////////////////////////////////////////////////////
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




	void Micromouse::Node::close()
	{
		closed = true;
	}

	void Micromouse::Node::open()
	{
		closed = false;
	}





#ifdef SFML_GRAPHICS_HPP

	// this is still rough code
	// it draws the node and some information about it
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

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * pos.y() + 16.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 14.0f , NODE_H * pos.y() + 16.0f ) , color );

				break;
			case Micromouse::W:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * pos.y() + 16.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * ( pos.y() + 1 ) + 15.0f ) , color );

				break;
			case Micromouse::E:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 14.0f , NODE_H * pos.y() + 16.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 14.0f , NODE_H * ( pos.y() + 1 ) + 14.0f ) , color );

				break;
			case Micromouse::S:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * ( pos.y() + 1 ) + 14.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 14.0f , NODE_H * ( pos.y() + 1 ) + 14.0f ) , color );

				break;
			case Micromouse::NW:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * pos.y() + 25.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 25.0f , NODE_H * pos.y() + 16.0f ) , color );

				break;
			case Micromouse::NE:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 13.0f , NODE_H * pos.y() + 25.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 4.0f , NODE_H * pos.y() + 16.0f ) , color );

				break;
			case Micromouse::SW:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * ( pos.y() + 1 ) + 6.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * pos.x() + 24.0f , NODE_H * ( pos.y() + 1 ) + 14.0f ) , color );

				break;
			case Micromouse::SE:

				line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 14.0f , NODE_H * ( pos.y() + 1 ) + 5.0f ) , color );
				line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * ( pos.x() + 1 ) + 5.0f , NODE_H * ( pos.y() + 1 ) + 14.0f ) , color );

				break;
			default:
				break;
			}

			sf::Text text;
			text.setFont( font );
			text.setPosition( sf::Vector2f( NODE_W * pos.x() + 16.0f , NODE_H * pos.y() + 25.0f ) );

			std::ostringstream ss;
			ss << pos.x() << ", " << pos.y();
			text.setString( ss.str() );

			text.setCharacterSize( 7 );
			renderWindow.draw( text );
			renderWindow.draw( line , 2 , sf::Lines );
		}
	}
#endif
}








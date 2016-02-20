#include <iostream>
#include "Maze.h"
#include <cstdlib>
#include<time.h>

using namespace std;


int main( int argc , char** argv )
{
	srand( time( NULL ) );

#ifdef SFML_GRAPHICS_HPP
	sf::RenderWindow renderWindow( sf::VideoMode( 1000 , 800 ) , "MicroMouse Sim" );
	sf::Event event;
	sf::Clock clock;

	//renderWindow.setKeyRepeatEnabled( false );


	//sf::ConvexShape mouseShape( 3 ); //set number of points for shape
	//mouseShape.setFillColor( sf::Color( 200 , 50 , 50 ) );

	//mouseShape.setPoint( 0 , sf::Vector2f( 0.0f , 0.0f ) );
	//mouseShape.setPoint( 1 , sf::Vector2f( 16.0f , 8.0f ) );
	//mouseShape.setPoint( 2 , sf::Vector2f( 0.0f , 16.0f ) );





	bool drawn = false;
	while ( renderWindow.isOpen() )
	{
		while ( renderWindow.pollEvent( event ) )
		{
			if ( event.type == sf::Event::EventType::Closed )
			{
				renderWindow.close();
			}

			if ( event.type == sf::Event::EventType::KeyPressed )
			{
				if ( event.key.code == sf::Keyboard::R )
				{
					//restart
				}
			}
		}
		if ( !drawn )
		{
		renderWindow.clear();

			pathfinding::Maze maze( renderWindow );
			maze.findPath( coord( 0 , 0 ) , coord( 14 , 11 ) );
			drawn = true;
		}

		sf::sleep( sf::milliseconds( 50 ) );
	}
#else
	pathfinding::Maze maze;
	maze.findPath( coord( 0 , 0 ) , coord( 14 , 11 ) );
#endif

	return 0;
}
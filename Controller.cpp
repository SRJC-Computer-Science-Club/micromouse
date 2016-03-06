#include <iostream>
#include "Controller.h"
#include "CompactMaze.h"

using namespace std;

namespace Micromouse
{

	Controller::Controller()
	{
		beginSimulation();
		CompactMaze maze = CompactMaze(31, 31);
		maze.generateRandomMaze();
		cout << maze;
	}






	Controller::~Controller()
	{
	}





	// This is the main loop that will virtually test the mouse
	void Controller::beginSimulation()
	{
		//Maze* maze = new Maze;

#ifdef SFML_GRAPHICS_HPP
		bool drawn = false;

		// to learn more on why these loops are like this read this:
		// http://www.sfml-dev.org/tutorials/2.0/graphics-draw.php
		while ( Window::isOpen() )
		{
			while ( Window::pollEvent( event ) )
			{
				if ( event.type == sf::Event::EventType::Closed )
				{
					Window::close();
				}

				if ( event.type == sf::Event::EventType::KeyPressed )
				{
					if ( event.key.code == sf::Keyboard::R )
					{
						// TODO: restart
					}
				}
			}

			if ( !drawn ) // we dont want it to draw over itself..yet
			{
				Window::clear();
				//maze->draw();
#endif
				//std::cout << maze->findPath( Vector::Pos( 2 , 2 ) , Vector::Pos( 14 , 11 ) );
#ifdef SFML_GRAPHICS_HPP

				Window::display();
				drawn = true;
			}


			sf::sleep( sf::milliseconds( 100 ) ); // 10fps
		}
#endif
	}
}
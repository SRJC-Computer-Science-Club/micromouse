#include "Controller.h"


using namespace Micromouse;


Controller::Controller()
{
	//maze = new Maze;

	//initializeFont();

	beginSimulation();
}


Controller::~Controller()
{
}


void Controller::beginSimulation()
{
	bool drawn = false;
	Maze* maze = new Maze;
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
					// restart
				}
			}
		}

		if ( !drawn )
		{
			Window::clear();
			maze->draw();

			maze->findPath( coord( 2 , 2 ) , coord( 14 , 11 ) );
			//maze->draw();
			// main sim loop
			Window::display();
			drawn = true;
		}


		sf::sleep( sf::milliseconds( 100 ) ); // 10fps
	}
}



#pragma once
#include "Maze.h"
#include "MouseBot.h"
#include "Drawable.h" //includes SFML





namespace Micromouse
{
	class Controller
	{
	public:
		Controller();
		~Controller();


	private:

		void beginSimulation();

#ifdef SFML_GRAPHICS_HPP
		sf::Event event;
		sf::Clock clock;
#endif

	};
}
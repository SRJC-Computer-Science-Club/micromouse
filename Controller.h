#pragma once
#include "Maze.h"
#include "Drawable.h" //includes SFML

#ifdef SFML_GRAPHICS_HPP
#include "Window.h"
#endif



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
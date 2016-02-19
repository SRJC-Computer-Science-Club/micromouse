#pragma once
#include "Maze.h"
#include "Window.h"

//used for gui
#include "SFML\Graphics.hpp" //uncomment this line to enable gui
// you will need sfml properly installed
// to get sfml
// download: http://www.sfml-dev.org/download/sfml/2.3.2/
// install: http://www.sfml-dev.org/tutorials/2.3/#getting-started
// video: https://www.youtube.com/playlist?list=PLS9MbmO_ssyCSyqZC2NEfblIa9_xSrMqR
// DO NOT include files in git because different people may need different versions


// TODO: change to a struct with members x,y for clarity
typedef std::pair< int , int > coord;



namespace Micromouse
{

	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to coordinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
//	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };


	class Controller
	{
	public:
		Controller();
		~Controller();



	private:

#ifdef SFML_GRAPHICS_HPP
		void beginSimulation();

		sf::Event event;
		sf::Clock clock;
#endif


	};
}

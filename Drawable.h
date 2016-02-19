#pragma once
#include "Window.h"


// TODO: change to a struct with members x,y for clarity
typedef std::pair< int , int > coord;

namespace Micromouse
{
	const int WINDOW_W = 1000 , WINDOW_H = 800;


	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to coordinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };



	class Drawable : public Window
	{
	public:

	protected:

		// draw is a pure virtual function meaning that any class that
		// inherents from Drawable will need to implement it.
		// this function will draw a representation of the 
		// object to the RenderWindow renderWindow
		virtual void draw() = 0;


	};
}
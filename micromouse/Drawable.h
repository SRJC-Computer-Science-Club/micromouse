#pragma once
#include "Window.h"

#ifdef SFML_GRAPHICS_HPP

namespace Micromouse
{
	const int WINDOW_W = 1000 , WINDOW_H = 800;




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

#endif
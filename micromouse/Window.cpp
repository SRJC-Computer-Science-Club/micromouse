#include "Window.h"

namespace Micromouse
{
#ifdef SFML_GRAPHICS_HPP

	sf::RenderWindow Window::renderWindow( sf::VideoMode( 720 , 720 ) , "MicroMouse Sim" );

	Window::Window()
	{
		initializeFont();
		renderWindow.setFramerateLimit(5000);
	}


	Window::~Window()
	{
	}


	sf::RenderWindow & Micromouse::Window::getRenderWindow()
	{
		return renderWindow;
	}	

	void Window::initializeFont()
	{
		//if ( !font.loadFromFile( "font.ttf" ) )
		{
			// error...
		//	throw;
		}
	}






	bool Micromouse::Window::isOpen()
	{
		return renderWindow.isOpen();
	}

	bool Micromouse::Window::pollEvent( sf::Event & event )
	{
		return renderWindow.pollEvent( event );
	}

	void Micromouse::Window::close()
	{
		renderWindow.close();
	}

	void Micromouse::Window::clear()
	{
		renderWindow.clear();
	}

	void Micromouse::Window::display()
	{
		renderWindow.display();
	}

#endif
}
#include "Window.h"

using namespace Micromouse;

sf::RenderWindow Window::renderWindow( sf::VideoMode( 1000 , 800 ) , "MicroMouse Sim" );

Window::Window()
{
	initializeFont();
}


Window::~Window()
{
}

sf::RenderWindow & Micromouse::Window::getRenderWindow()
{
	return renderWindow;
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


void Window::initializeFont()
{
	if ( !font.loadFromFile( "font.ttf" ) )
	{
		// error...
		throw;
	}
}

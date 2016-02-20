#pragma once


//used for gui
#include "SFML\Graphics.hpp" //comment this line if compile error
// do so should disable the gui entirely
// to get sfml
// download: http://www.sfml-dev.org/download/sfml/2.3.2/
// install: http://www.sfml-dev.org/tutorials/2.3/#getting-started
// video: https://www.youtube.com/playlist?list=PLS9MbmO_ssyCSyqZC2NEfblIa9_xSrMqR
// do not include files in git because different people will need different versions



class Drawable
{
public:
	Drawable();
	~Drawable();

	// draw is a pure virtual function meaning that any class that
	// inherents from Drawable will need to implement it.
	// this function will draw a representation of the calling 
	// object to the RenderWindow rw

	virtual void draw( sf::RenderWindow & rw ) = 0;

};


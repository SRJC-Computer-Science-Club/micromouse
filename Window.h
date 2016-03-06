#pragma once

//used for gui
#include "SFML\Graphics.hpp" //uncomment this line to enable gui
// you will need sfml properly installed
// to get sfml
// download: http://www.sfml-dev.org/download/sfml/2.3.2/
// install: http://www.sfml-dev.org/tutorials/2.3/#getting-started
// video: https://www.youtube.com/playlist?list=PLS9MbmO_ssyCSyqZC2NEfblIa9_xSrMqR
// DO NOT include files in git because different people may need different versions

#ifdef SFML_GRAPHICS_HPP

namespace Micromouse
{
	class Window
	{
	public:
		Window();
		~Window();



		// exposes sfml functions for easier use
		static bool isOpen();
		static bool pollEvent( sf::Event& event );
		static void close();
		static void clear();
		static void display();

		static sf::RenderWindow& getRenderWindow();

	protected:

		static sf::RenderWindow renderWindow;
		sf::Font font;

	private:

		void initializeFont();
	};
}

#endif

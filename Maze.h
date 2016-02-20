#pragma once
#include <utility> //pair
#include "Node.h"
#include "Drawable.h"

//used for gui
#include "SFML\Graphics.hpp" //comment this line if compile error
// download: http://www.sfml-dev.org/download/sfml/2.3.2/
// install: http://www.sfml-dev.org/tutorials/2.3/#getting-started
// video: https://www.youtube.com/playlist?list=PLS9MbmO_ssyCSyqZC2NEfblIa9_xSrMqR
// do not include files in github because different people will need different versions





//TODO come up with a better name for than pathfinding
namespace pathfinding
{
	const int MAZE_W = 16 , MAZE_H = 16;

#ifdef SFML_GRAPHICS_HPP
	const int NODE_W = 48 , NODE_H = 48;
#endif


	class Maze : public Drawable
	{
	public:

#ifdef SFML_GRAPHICS_HPP
		Maze( sf::RenderWindow& rw );
#else
		Maze();
#endif

		~Maze();

		int findPath( coord start , coord end );
		int findPath( const Node& start , const Node& end );

	private:
		Node* maze[ MAZE_H ][ MAZE_W ];

		Node* getNeighborNode( coord pos , direction dir );

#ifdef SFML_GRAPHICS_HPP
		sf::RenderWindow& rw;
		void drawNode( int i , int j );
#endif

	};
}
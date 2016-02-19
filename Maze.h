#pragma once
#include <utility> //pair
#include "Drawable.h"



namespace Micromouse
{
	const int MAZE_W = 16 , MAZE_H = 16;

	class Node;

	class Maze : public Drawable
	{
	public:
		Maze();
		~Maze();

		int findPath( coord start , coord end );
		int findPath( const Node * const start , const Node * const end );

#ifdef SFML_GRAPHICS_HPP
		void draw();
#endif

	private:
		Node* maze[ MAZE_H ][ MAZE_W ];
		Node* getNeighborNode( coord pos , direction dir );
		void initNodes();

#ifdef SFML_GRAPHICS_HPP
		void drawLine(coord begin , coord end);
#endif


	};
}
#pragma once
#include <utility> //pair
#include "Drawable.h"
#include "Node.h"
#include "Coord.h"

namespace Micromouse
{
	const int MAZE_W = 16 , MAZE_H = 16;

#ifdef SFML_GRAPHICS_HPP
	class Maze : public Drawable
#else
	class Maze
#endif
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Coords to utilized by the motion controller
		int findPath( Coord start , Coord end );
		int findPath( const Node * const start , const Node * const end );

#ifdef SFML_GRAPHICS_HPP
		void draw(); // draws the maze to the renderWindow
#endif

	private:
		// returns a pointer to the node in the direction 'dir' from the given Coord 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( Coord pos , direction dir );


		// populates 'maze' with Nodes
		void initNodes();

		// a 2D array of Nodes that represents the physical maze
		Node* maze[ MAZE_W ][ MAZE_H ];

#ifdef SFML_GRAPHICS_HPP
		void drawLine( Coord begin , Coord end );
#endif


	};
}
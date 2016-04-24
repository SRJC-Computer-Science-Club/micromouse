#pragma once
#include "Node.h"
#include "Vector.h"
#include "Path.h"
#include "FlagMatrix.h"


namespace Micromouse
{
#ifdef SFML_GRAPHICS_HPP
	class Maze : public Drawable
#else
	class Maze
#endif
	{
	public:
		Maze();
		~Maze();


		// TODO it should return a list of Vectors to utilized by the motion controller
		Path * findPath( PositionVector start , PositionVector end );
		Path * findPath( const Node * const start , const Node * const end );

		// returns a Node from the maze
		// 'pos' is the position of the Node being returned
		Node* getNode( PositionVector pos );

		// adds a Node to the Maze
		// 'pos' is the position of the new Node being created
		void addNode( PositionVector newPos );

		// returns a pointer to the node in the direction 'dir' from the given Pos 'pos'
		// if no such node exists then nullptr is returned
		Node* getNeighborNode( PositionVector pos , direction dir );

		//Sets the open flag at the given position.
		//If the position is outside the maze, nothing happens.
		void setOpen(bool flag, int x, int y);
		void setOpen(bool flag, PositionVector pos);


		//Sets the explored flag at the given position.
		//If the position is outside the maze, nothing happens.
		void setExplored(bool flag, int x, int y);
		void setExplored(bool flag, PositionVector pos);

		//Returns the open flag at the given position.
		//If the position is outside the maze, returns false.
		bool isOpen(int x, int y) const;
		bool isOpen(PositionVector pos) const;


		//Returns the explored flag at the given position.
		//If the position is outside the maze, returns false.
		bool isExplored(int x, int y) const;
		bool isExplored(PositionVector pos) const;

		//Returns true if the given position in within the maze.
		//( 0 <= x < NUM_NODES_W and 0 <= y < NUM_NODES_H )
		bool isInsideMaze(int x, int y) const;
		bool isInsideMaze(PositionVector pos) const;

#ifdef SFML_GRAPHICS_HPP
		void draw(); // draws the maze to the renderWindow
#endif

	private:

		// creates a Path object after findPath has been called
		// 'node' is the finish node in the path
		// the path is created by working backwards from end node to start node
		Path* createPath( const Node* node );

		// populates 'maze' with Nodes
		void initNodes();

		// returns the Nodes in maze to their initial sates
		void resetNodes();
		
		// a 2D array of Nodes that represents the physical maze
		Node* maze[ NUM_NODES_W ][ NUM_NODES_H ];

		// a 2D array of flags (booleans), that denote whether or not a cell, edge, or corner is open.
		FlagMatrix open;

		//A 2D array of flags (booleans), that denote whether or not a cell, edge, or corner has been explored.
		FlagMatrix explored;

#ifdef SFML_GRAPHICS_HPP
		void drawLine(PositionVector begin, PositionVector end);
#endif

	};

	//Prints out a picture of the maze for debugging.
	//Just use: log( DEBUGX ) << maze;
#ifdef __MK20DX256__ // Teensy Compile
#else
	std::ostream& operator<<(std::ostream& out, const Maze& maze);
#endif
}
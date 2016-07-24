#include <vector>
#include <algorithm>
#include <math.h>
#include "Maze.h"
#include <assert.h>

namespace Micromouse
{
	// constructors //////////////////////////////////////////////////

	Maze::Maze()
	{
		initNodes();
	}



	Maze::~Maze()
	{
	}



	// this is to allow the sorting of the vector of Nodes
	// sorts in descending order
	bool nodeComparator( const Node* lhs , const Node* rhs )
	{
		return lhs->getF() > rhs->getF();
	}



	Path * Maze::findPath( PositionVector start , PositionVector end , bool isMapping , NodePairList* passageNodes)
	{
		resetNodes();

		// if pathfinding during mapping
		if (passageNodes != nullptr)
		{
			// Assert that both start and end have been explored
			// This is needed to guarantee that NodePairs will be complete
			assert(getNode(start)->isExplored() && getNode(end)->isExplored());

			// a NodePairList should on be used during mapping
			assert(isMapping);
		}

		std::vector< Node* > openNodes;

		// assume 1/2 of the maze will need to be searched on average;
		// this prevents too many resizes, idk if this is optimal I was just estimating
		openNodes.reserve( static_cast< int >( NUM_NODES_W * NUM_NODES_H * 0.5f ) );

		// the start node is added to openNodes
		openNodes.push_back( getNode( start ) );

		// initialize the movement cost to 0 for the first node
		getNode( start )->setG( 0 );

		Node* currentNode;
		Node* neighborNode;
		int tentative_G;

		// While there are still open nodes remaining
		while ( !openNodes.empty() )
		{
			// sort the nodes in descending order by F value
			// we sort by descending so we can later us pop_back()
			std::sort( openNodes.begin() , openNodes.end() , nodeComparator ); 

			// get the node with the lowest F value
			currentNode = openNodes.back();

			// if we are at the end node then we are done!
			if ( currentNode == getNode( end ) ) 
			{
#ifdef SFML_GRAPHICS_HPP
				Node* temp = currentNode;
				while ( temp->getParent() != nullptr ) // draw the path pack to the start node
				{
					if (isMapping)
					{
						drawLine(temp->getPos(), temp->getParent()->getPos(), sf::Color(220, 30, 30));
					}
					else
					{
						drawLine(temp->getPos(), temp->getParent()->getPos(), sf::Color(255, 255, 50));
					}

					temp = temp->getParent();
				}
#endif
				// create a Path object for motion control to utilize
				return createPath( currentNode, isMapping, passageNodes ); 
			}

			openNodes.pop_back();
			currentNode->close();

			// loop through neighbor nodes
			for ( direction dir = N; dir != NONE; ++dir )
			{
				neighborNode = getNeighborNode( currentNode->getPos() , dir );

				if ( neighborNode == nullptr )
				{
					continue; // there is no neighbor node in this direction
				}

				if ( neighborNode->isClosed() )
				{
					continue; // Ignore the neighbor which is already evaluated
				}

				if ( !isMapping && !neighborNode->isExplored())
				{
					continue; // Ignore the unexplored nodes if we arent mapping
				}


				tentative_G = currentNode->getG();

				// if moved diagnal add 14, else moved straight add 10
				tentative_G += ( dir == direction::NW || dir == direction::SW || dir == direction::NE || dir == direction::SE ) ? 14 : 10; 


				//if neighborNode is not already in openNodes then add id
				if ( std::find( openNodes.begin() , openNodes.end() , neighborNode ) == openNodes.end() )
				{
					openNodes.push_back( neighborNode );
				}
				// else the neighborNode is already in openNodes
				// if new path to neighborNode is worse than previous
				else if ( tentative_G >= neighborNode->getG() )
				{
					continue; //this is not a better path
				}

				//if we made it to this point then
				//this path is the best so far
				neighborNode->setParent( currentNode );
				neighborNode->setDir( dir );
				neighborNode->setG( tentative_G );
				neighborNode->setF( tentative_G + 0 /*TODO calculate Hueristic here*/ );
			}
		}

		// no path was found
		// this should never happen in real maze
		// TODO throw error if this is reached in real testing
		return nullptr;
	}






	// Retruns the Node at the given position.
	Node* Maze::getNode( PositionVector pos ) const
	{
		return maze[pos.x()][pos.y()];
	}



	// adds a new node to the maze at the given position
	void Maze::addNode(PositionVector pos)
	{
		assert(pos.isValidPosition());
		maze[pos.x()][pos.y()] = new Node(pos);
	}

	void Maze::removeNode(PositionVector pos)
	{
		assert(pos.isValidPosition());
		delete maze[pos.x()][pos.y()];
		maze[pos.x()][pos.y()] = nullptr;
	}



	// returns a pointer to the neighbor node at direction dir from pos
	Node * Maze::getNeighborNode(PositionVector pos, direction dir)
	{
		// Uses old direction enum order
		// int x = pos.x() + dir % 3 - 1;
		// int y = pos.y() + dir / 3 - 1;
		//if (x >= 0 && x < NUM_NODES_W && y >= 0 && y < NUM_NODES_H) { return maze[x][y]; }

		if (dir == NW || dir == SW || dir == SE || dir == NE)
		{
			return nullptr;
		}


		pos = pos + dir;

		if (pos.x() >= 0 && pos.x() < NUM_NODES_W && pos.y() >= 0 && pos.y() < NUM_NODES_H)
		{
			return maze[pos.x()][pos.y()];
		}


		/*       x
		-1  0  1
		----------
		1| NW| N |NE|
		|---+---+--|
		y 0| W |   | E|
		|---+---+--|
		-1| SW| s  SE|
		----------
		*/

		return nullptr;
	}



	void Maze::setExplored( PositionVector pos )
	{
		Node* node = getNode(pos);

		if (node != nullptr)
		{
			node->setExplored();
		}
	}



	bool Maze::isExplored(PositionVector pos) const
	{
		Node* node = getNode(pos);

		if (node != nullptr)
		{
			return node->isExplored();
		}

		return false;
	}



	Path * Maze::createPath( const Node * node , bool isMapping , NodePairList* passageNodes)
	{
		Path* path = new Path;
		direction travelDir = node->getDir();

		const Node* passageNodeTemp;
		const Node* previousNode = node;

		int magnitude = 1;
		node = node->getParent();

		// used to detect the transition between explored and unexplored nodes
		// if the edge detectors are not equal then an edge is present
		bool edgeDetectorA;
		bool edgeDetectorB = true;



		// while there is more to the path to traverse
		while (node != nullptr)
		{
			//if we are at the beginning of the path or if the path is not straight 
			// or we are mapping 
			if ( isMapping || node->getDir() != travelDir || passageNodes != nullptr)
			{
				// add a step to the path to define the direction and distance needed to travel
				path->addStep(DirectionVector(travelDir, magnitude));

				travelDir = node->getDir();
				magnitude = 0;
			}
			//else the path is straight so no need for a step

			
			// the short circuit protects the second half of the boolean expression
			edgeDetectorA = (node != nullptr && node->isExplored());

			// if the edgeDectors are not equal then we are at a boundary between
			// explored and unexplored nodes
			if (passageNodes != nullptr && edgeDetectorA != edgeDetectorB)//an edge!
			{
				// edgeDetectorB will always be true first since we are 
				// guaranteed to start and end at explored nodes
				if (edgeDetectorB)
				{
					// we want to make sure we set it the previous node
					// since the current one is unexplored.
					// it is guaranteed that previousNode will be explored
					passageNodeTemp = previousNode;
				}
				else
				{
#ifdef SFML_GRAPHICS_HPP
					drawCircle(passageNodeTemp->getPos(), 6, sf::Color(200, 120, 20));
					drawCircle(node->getPos(), 6, sf::Color(200,120,20));
#endif
					// we now have a pair of nodes that represent an entrance
					// and exit from unexplored nodes
					passageNodes->push_back( std::make_pair( node , passageNodeTemp) );
				}
			}

			previousNode = node;
			node = node->getParent();

			edgeDetectorB = edgeDetectorA;

			magnitude++;
		}

		return path;
	}



	// populates the maze with Nodes
	void Maze::initNodes()
	{
		for ( int x = 0; x < NUM_NODES_W; x++ )
		{
			for ( int y = 0; y < NUM_NODES_H; y++ )
			{
				if (isValidPosition( x, y) )
				{
					maze[ x ][ y ] = new Node( PositionVector(x,y) );
				}
				else
				{
					maze[x][y] = nullptr;
				}
			}
		}
	}



	void Maze::resetNodes()
	{
		for (size_t i = 0; i < NUM_NODES_W; i++)
		{
			for (size_t j = 0; j < NUM_NODES_H; j++)
			{
				if (maze[i][j] != nullptr)
				{
					maze[i][j]->reset();
				}
			}
		}
	}




	void Maze::removeExcessFinshNodes()
	{
		Node * tempNode;
		for (int i = -2; i <= 2; i++)
		{
			for (int j = -2; j <= 2; j++)
			{
				tempNode = getNode(PositionVector(i, j) + PositionVector::FINISH);
				if (tempNode != nullptr && !tempNode->isExplored())
				{
					removeNode(PositionVector(i, j) + PositionVector::FINISH);
				}
			}
		}
	}


#ifdef SFML_GRAPHICS_HPP
	void Maze::drawLine(PositionVector begin , PositionVector end , sf::Color color )
	{
		//sf::Vertex line[ 2 ];
		//line[ 0 ] = sf::Vertex( sf::Vector2f( NODE_W * begin.x() + 60.0f , NODE_H * (NUM_NODES_H - 1 - begin.y()) + 60.0f ) , color );
		//line[ 1 ] = sf::Vertex( sf::Vector2f( NODE_W * end.x() + 60.0f , NODE_H *(NUM_NODES_H - 1 - end.y()) + 60.0f ) , color );
		//renderWindow.draw( line , 2 , sf::Lines );
		//Window::display();
		//renderWindow.draw(line, 2, sf::Lines);
		//Window::display();
	}


	void Maze::drawCircle(PositionVector pos, int rad, sf::Color color, bool fill , sf::Color colorFill )
	{

		//rad *= NODE_W / 20.f;
		//sf::CircleShape circle(rad );
		//
		//circle.setOutlineThickness(2);
		//circle.setOutlineColor(color);

		//if (fill)
		//{
		//	circle.setFillColor(colorFill);
		//}
		//else
		//{
		//	circle.setFillColor(sf::Color::Transparent);
		//}

		//circle.setOrigin(rad, rad);
		//circle.setPosition(pos.x() * NODE_W + 60, (NUM_NODES_H - 1 - pos.y()) * NODE_H + 60);
		//renderWindow.draw(circle);
		//Window::display();
		//renderWindow.draw(circle);
		//Window::display();
	}



	void Maze::draw()
	{
		for ( int x = 0; x < MAZE_W; x++ )
		{
			for ( int y = 0; y < MAZE_H; y++ )
			{
				//maze[ x ][ y ]->draw();
			}
		}
	}
#endif




#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
	std::ostream& operator<<(std::ostream& out, const Maze& maze)
	{
		out << std::endl << "+ ";

		for (int x = 0; x < NUM_NODES_W; x++)
		{
			out << "- ";
		}

		out << "+" << std::endl;

		for (int y = NUM_NODES_H - 1; y >= 0; y--)
		{
			out << "| ";

			for (int x = 0; x < NUM_NODES_W; x++)
			{
				if (maze.isExplored(PositionVector(x,y)))
				{
					if (maze.getNode(PositionVector(x,y)) != nullptr)
					{
						out << "  ";
					}
					else
					{
						if (y % 2 == 0 && x % 2 == 1)
						{
							out << "| ";
						}
						else if (y % 2 == 1 && x % 2 == 0)
						{
							out << "- ";
						}
						else
						{
							out << "+ ";
						}
					}
				}
				else
				{
					out << "+ ";
				}
			}
			out << "|" << std::endl;
		}

		out << "+ ";

		for (int x = 0; x < NUM_NODES_W; x++)
		{
			out << "- ";
		}

		out << "+" << std::endl;

		return out;
	}
#endif
}

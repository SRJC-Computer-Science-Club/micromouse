/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/



#include "MouseBot.h"
#include "Logger.h"
#include "ButtonFlag.h"



namespace Micromouse
{
#define SQRT_OF_TWO (1.414213f)

	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot(int x, int y)
	{
		log(DEBUG2) << "Creating MouseBot at (" << x << ", " << y << ")";

		setPos(x, y);
		maze = new Maze();

#ifdef __MK20DX256__ // Teensy Compile
#else
		// If compiled for PC
		virtualMaze = new VirtualMaze(NUM_NODES_W, NUM_NODES_H);
		virtualMaze->generateRandomMaze();

		//logC(INFO) << "Randomly generated a virtual maze:\n";
		//logC(INFO) << *virtualMaze << "\n";
#endif
	}



	MouseBot::~MouseBot()
	{
		delete maze;

#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
		delete virtualMaze;
#endif
	}





	/**** SET / GET FUNCTIONS ****/

	PositionVector MouseBot::getPos()
	{
		return position;
	}

	direction MouseBot::getFacing()
	{
		return facing;
	}

	void MouseBot::setPos(int x, int y)
	{
		setPos(PositionVector(x, y));
	}

	void MouseBot::setPos(PositionVector pos)
	{
		this->position = pos;
	}

	void MouseBot::resetToOrigin()
	{
		position = PositionVector(0, 0);
		facing = N;
	}





	/**** MAPPING FUNCTIONS ****/

	int MouseBot::mapMaze()
	{
		log(DEBUG1) << "Mapping Maze...";
		
		moves = 0; // Reset moves made to zero

		Path* path;	// Used for pathfinding	
		NodePairList nodePairList; // Vector of node pairs;
		bool foundFinish = false; // If the maze finish has been found

		// Set the starting and finish node as explored
		maze->getNode(PositionVector::START)->setExplored();
		maze->getNode(PositionVector::FINISH)->setExplored();
		
		for (;;)
		{
			BUTTONFLAG // Used to abort operation if button is pressed

			// Find a path from start to finish generating a NodePair for 
			// everytime the path goes into unexplored nodes
			path = maze->findPath(PositionVector::START, PositionVector::FINISH, true, &nodePairList);
			delete path;
			
			// If the shortest path was completely contained within explored nodes
			// then no NodePairs were created and we can stop mapping
			if (nodePairList.size() == 0) break; 

			// Otherwise we do not have the shortest path fully explored
			// So we find the closest node at the boundry between explored and 
			// unexplored nodes
			NodePair closestNodePair = getClosestNodePair(nodePairList);
			nodePairList.clear();

			// Travel to the nearest node we just found by only pathfinding on
			// explored nodes to guarantee we can get there safely
			path = maze->findPath(position, closestNodePair.first->getPos() );
			followPath(path);

			for (;;)
			{
				BUTTONFLAG // Used to abort operation if button is pressed

				// Attempt to travel from the first node of the pair to the second
				// Stop if the path is blocked
				path = maze->findPath(position, closestNodePair.second->getPos(), true);
				followPathUntilBroken(path);

				// Find a new path from start to finish incase it was changed by
				// the recently discovered walls
				path = maze->findPath(PositionVector::START, PositionVector::FINISH, true, &nodePairList);
				delete path;

				// If the shortest path was completely contained within explored nodes
				// then no NodePairs were created and we can stop mapping
				if (nodePairList.size() == 0) goto FINISH_MAPPING;

				// If we are at the second node of the pair
				if (position == closestNodePair.second->getPos()) break;
			}

			// The first time this line is reached is when we are at the 
			// finish of the maze. We can then remove all remaining nodes 
			// around the center because we know they must be walls
			if (!foundFinish)
			{
				maze->removeExcessFinshNodes();
				foundFinish = true;
			}

			nodePairList.clear();
		} 

		// exit point for the inner loop
		FINISH_MAPPING:

		logC(INFO) << "Mapped maze in: " << moves << " moves";

		returnToStart();

		BUTTONEXIT
		return moves;
	}



	void MouseBot::runMaze()
	{
		log(DEBUG1) << "Run Maze";

		Path* pathCenter = maze->findPath(position, PositionVector::FINISH);
		followPath(pathCenter);
		delete pathCenter;

		returnToStart();
	}



	void MouseBot::resetMaze()
	{
		delete maze;
		maze = new Maze();

	}



	void MouseBot::returnToStart()
	{
#ifdef __MK20DX256__ // Teensy Compile
		delay(400);
#endif
		Path* pathHome = maze->findPath(position, PositionVector::START);
		followPath(pathHome);
		rotate(S);
		delete pathHome;
	}



	void MouseBot::lookAround()
	{
		logC(DEBUG4) << "lookAround()";

		maze->setExplored( position);

		PositionVector pos = position + facing; //forward
		
		// if the position is valid
		if (pos.isValidPosition())
		{
			// if it is clear forward then set the node explored
			if (isClearForward())
			{
				maze->setExplored(pos);
			}
			// else there is a wall so we remove the node
			else
			{
				maze->removeNode(pos);

#ifdef SFML_GRAPHICS_HPP
				maze->drawLine(pos + (facing+E), pos + (facing + W) , sf::Color(250, 250, 250));
#endif
			}
		}
		
		// do the same for the left and right directions

		pos = position + (facing + E); //right

		if (pos.isValidPosition())
		{
			if (isClearRight())
			{
				maze->setExplored(pos);
			}
			else
			{
				maze->removeNode(pos);
#ifdef SFML_GRAPHICS_HPP
				maze->drawLine(pos + facing, pos + (facing + S), sf::Color(250, 250, 250));
#endif
			}
		}


		pos = position + (facing + W); //right

		if (pos.isValidPosition())
		{
			if (isClearLeft())
			{
				maze->setExplored(pos);
			}
			else
			{
				maze->removeNode(pos);

#ifdef SFML_GRAPHICS_HPP
				maze->drawLine(pos + facing, pos + (facing + S), sf::Color(250, 250, 250));
#endif
			}
		}
	}




	NodePair MouseBot::getClosestNodePair(NodePairList & nodePairList)
	{
		NodePair closestNodePair;
		bool isClosestFirst;
		int shortestDistance = INT_MAX;
		int distance;

		// iterate through the nodePairs
		for (NodePairList::iterator itr = nodePairList.begin(); itr != nodePairList.end(); ++itr)
		{
			//first of pair
			distance = pow(itr->first->getPos().x() - position.x(), 2) + pow(itr->first->getPos().y() - position.y(), 2);

			if ( distance < shortestDistance)
			{
				closestNodePair = *itr;
				isClosestFirst = true;
				shortestDistance = distance;
			}

			//second of pair
			distance = pow(itr->second->getPos().x() - position.x(), 2) + pow(itr->second->getPos().y() - position.y(), 2);

			if (distance < shortestDistance)
			{
				closestNodePair = *itr;
				isClosestFirst = false;
				shortestDistance = distance;
			}
		}

		// make it so the closest node of the two always comes first
		return isClosestFirst ? closestNodePair : std::make_pair( closestNodePair.second , closestNodePair.first );
	}



	bool MouseBot::isClearForward()
	{
#ifdef __MK20DX256__ // Teensy Compile
		return robotIO.isClearForward();
#else // PC compile
		PositionVector pos = position + (facing + N);

		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}



	bool MouseBot::isClearRight()
	{
#ifdef __MK20DX256__ // Teensy Compile
		return robotIO.isClearRight();
#else // PC compile
		PositionVector pos = position + (facing + E);

		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}



	bool MouseBot::isClearLeft()
	{
#ifdef __MK20DX256__ // Teensy Compile
		return robotIO.isClearLeft();
#else // PC compile
		PositionVector pos = position + (facing + W);

		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}





	/**** MOVEMENT FUNCTIONS ****/
	void MouseBot::move(direction dir)
	{
#ifdef SFML_GRAPHICS_HPP
		lastPosition = position;
#endif
		position = position + dir;
		movementHistory.push(dir);

#ifdef SFML_GRAPHICS_HPP
		maze->drawCircle(lastPosition, 3, sf::Color(0, 0, 0),true, sf::Color(10, 80, 0));
		maze->drawCircle(position, 3, sf::Color(10, 230, 0), true, sf::Color(10, 250, 0));

		//maze->drawCircle(lastPosition+facing, 2, sf::Color(0, 0, 0), true, sf::Color(10, 80, 0));
		maze->drawCircle(position+facing, 2, sf::Color(10, 230, 230), true, sf::Color(10, 250, 230));
		moves++;
#endif
	}



	void MouseBot::followPath(Path* path, bool keepPath)
	{
		// make sure there is a path
		if (path != nullptr)
		{
			DirectionVector dirVec(N, 0);

			// while there is still some path remaining
			while (!path->empty())
			{
				BUTTONFLAG

				// get the next step of the path
				dirVec = path->popStep();

				// follow the path
				rotateToFaceDirection(dirVec.dir());
				moveForward(dirVec.mag());
			}
		}
		else
		{
			log(ERROR) << "COULD NOT FIND PATH DURING RUNNING";
		}

		BUTTONEXIT

		if ( !keepPath)
		{
			delete path;
		}

		return;
	}



	void MouseBot::followPathUntilBroken(Path * path, bool keepPath)
	{
		// make sure there is a path
		if (path != nullptr)
		{
			DirectionVector dirVec( N , 0 );

			// while there is still some path remaining
			while (!path->empty())
			{
				BUTTONFLAG
	
				// get the next step of the path
				dirVec = path->popStep();
				maze->drawCircle(position + facing, 2, sf::Color(10, 230, 230), true, sf::Color(10, 250, 230));

				lookAround();
				// if the next step in the path is unobstructed
				// then follow the path
				if ( maze->getNeighborNode( position , dirVec.dir() ) != nullptr )
				{
					rotateToFaceDirection(dirVec.dir());
					moveForward();
				}
				else // desired path was obstructed
				{
					goto EXIT;
				}
			}
		}
		else
		{
			log(ERROR) << "COULD NOT FIND PATH DURING MAPPING";
		}

		EXIT:
		BUTTONEXIT

		if (!keepPath)
		{
			delete path;
		}

		return;
	}





	void MouseBot::testMotors()
	{
#ifdef __MK20DX256__ // Teensy Compile
		robotIO.testMotors();
#endif
	}


	void MouseBot::testIR()
	{
		robotIO.testIR();
	}



	void MouseBot::testRotate()
	{
		robotIO.testRotate();
	}



	void MouseBot::moveForward(int numNodes)
	{
		for (int i = 0; i < numNodes; i++)
		{
			move(facing);
		}

		float magnitude = numNodes * MM_PER_NODE;
		
		if (facing == NE || facing == SE || facing == SW || facing == NW)
		{
			magnitude *= SQRT_OF_TWO;
		}

#ifdef __MK20DX256__ // Teensy Compile
		robotIO.moveForward(magnitude);
		delay(500);
#endif
	}



	void MouseBot::rotate(direction dir)
	{
		facing = facing + dir;

#ifdef __MK20DX256__ // Teensy Compile
		switch (dir)
		{
		case NE:	robotIO.rotate(45);		break;
		case E:		robotIO.rotate(90);		break;
		case SE:	robotIO.rotate(135);	break;
		case S:		robotIO.rotate(180);	break;
		case SW:	robotIO.rotate(-135);	break;
		case W:		robotIO.rotate(-90);	break;
		case NW:	robotIO.rotate(-45);	break;
		}
		delay(200);
#endif
	}



	void MouseBot::rotateToFaceDirection(direction dir)
	{
		rotate(dir - facing);
		maze->drawCircle(position + facing, 2, sf::Color(10, 230, 230), true, sf::Color(10, 250, 230));
	}



	int MouseBot::incrementSpeed()
	{
		speed = speed % MAX_SPEED + 1;
		log(INFO) << "Mouse Speed: " << speed;

		return 0;
	}


	int MouseBot::getSpeed()
	{
		return speed;
	}


	void MouseBot::setSpeed( int spd )
	{
		speed = spd;
		assert(speed > 0 && speed <= MAX_SPEED);
	}


	void MouseBot::CalibrateIRSensors()
	{
		robotIO.calibrateIRSensors();
	}







#ifdef SFML_GRAPHICS_HPP
	void MouseBot::draw()
	{

		//Window::clear();
		//virtualMaze->draw();
		sf::CircleShape circle(3);
		circle.setFillColor(color);
		circle.setOrigin(4, 4);
		circle.setPosition(position.x() * 20 + 60,(NUM_NODES_H - 1 - position.y()) * 20 + 60);
		//sf::sleep(sf::milliseconds(50)); // 10fps
		renderWindow.draw(circle);

		circle.setPosition(lastPosition.x() * 20 + 60, (NUM_NODES_H - 1 - lastPosition.y()) * 20 + 60);
		//sf::sleep(sf::milliseconds(50)); // 10fps
		renderWindow.draw(circle);

		Window::display();
		lastPosition = position;
	}
#endif


}


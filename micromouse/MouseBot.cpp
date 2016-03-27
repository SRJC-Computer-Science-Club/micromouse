/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "MouseBot.h"
#include <stack>
#include "Logger.h"

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot(int x, int y)
	{
		log(DEBUG2) << "Creating MouseBot at (" << x << ", " << y << ")";

		setPos(x, y);

#ifdef __MK20DX256__
		// If compiled for Teensy

		//robotIO = RobotIO();
		// 1. the default constructor is implicitly called since 
		//the variable was of type RobotIO, and not RobotIO*, but
		// this alone would not cause an error
		//
		// 2. RobotIO contains constants which makes the = operator not work because it knows it can't copy the consts 
		// giving this error
		//MouseBot.cpp:33: error: use of deleted function 'Micromouse::RobotIO& Micromouse::RobotIO::operator=(const Micromouse::RobotIO&)'
		// i made the constants static as they should be to avoid this
#else
		// If compiled for PC
		virtualMaze = new VirtualMaze(NUM_NODES_W, NUM_NODES_H);
		virtualMaze->generateRandomMaze();

		logC(INFO) << "Randomly generated a virtual maze:\n";
		//logC(INFO) << *virtualMaze << "\n";
#endif
	}

	MouseBot::~MouseBot()
	{
#ifdef __MK20DX256__
		// If compiled for Teensy
#else
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





	/**** MAPPING FUNCTIONS ****/

	void MouseBot::mapMaze()
	{
		log(DEBUG2) << "Starting Mapping";

		maze.setOpen(true, position);
		maze.addNode(position);
		maze.setExplored(true, position);

		std::stack<PositionVector*> choicePositions = std::stack<PositionVector*>();
		choicePositions.push(new PositionVector(position));
		lookAround();
		
		while (!choicePositions.empty())
		{
			//logC(DEBUG1) << maze;

			PositionVector* pos = choicePositions.top();
			choicePositions.pop();

			while (position != *pos)
			{
				backtrack();
			}

			delete pos;

			logC(DEBUG3) << "Number of possible directions: " << numPossibleDirections();
			while (numPossibleDirections() > 0)
			{
				if (numPossibleDirections() > 1)
				{
					choicePositions.push(new PositionVector(position));
				}
				direction dir = pickPossibleDirection();
				rotateToFaceDirection(dir);
				logC(DEBUG3) << "Traveled " << dir;
				moveForward();
				lookAround();
				moveForward();
				lookAround();
			}
		}

		//logC(INFO) << maze;
		//logC(INFO) << "Mapped maze:\n";
	}

	void MouseBot::lookAround()
	{
		if (isClearForward())
		{
			PositionVector pos = position + (facing + N);
			maze.setOpen(true, pos);
			maze.addNode(pos);
		}
		if (isClearRight())
		{
			PositionVector pos = position + (facing + E);
			maze.setOpen(true, pos);
			maze.addNode(pos);
		}
		if (isClearLeft())
		{
			PositionVector pos = position + (facing + W);
			maze.setOpen(true, pos);
			maze.addNode(pos);
		}
		maze.setExplored(true, position + (facing + N));
		maze.setExplored(true, position + (facing + E));
		maze.setExplored(true, position + (facing + W));
	}

	bool MouseBot::isPossibleDirection(direction dir)
	{
		return maze.isInsideMaze(position + dir) && maze.isOpen(position + dir) && !maze.isExplored((position + dir) + dir);
	}

	int MouseBot::numPossibleDirections()
	{
		int n = 0;
		if (isPossibleDirection(N)) n++;
		if (isPossibleDirection(E)) n++;
		if (isPossibleDirection(S)) n++;
		if (isPossibleDirection(W)) n++;
		return n;
	}

	direction MouseBot::pickPossibleDirection()
	{
		if (isPossibleDirection(N)) return N;
		if (isPossibleDirection(E)) return E;
		if (isPossibleDirection(S)) return S;
		if (isPossibleDirection(W)) return W;
	}

	bool MouseBot::isClearForward()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearForward();

#else
		// If compiled for PC

		PositionVector pos = position + (facing + N);
		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}

	bool MouseBot::isClearRight()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearRight();

#else
		// If compiled for PC

		PositionVector pos = position + (facing + E);
		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}

	bool MouseBot::isClearLeft()
	{

#ifdef __MK20DX256__
		// If compiled for Teensy

		return robotIO.isClearLeft();

#else
		// If compiled for PC

		PositionVector pos = position + (facing + W);
		return virtualMaze->isInsideMaze(pos) && virtualMaze->isOpen(pos);
#endif
	}





	/**** MOVEMENT FUNCTIONS ****/

	void MouseBot::move(direction dir)
	{
		position = position + dir;
		movementHistory.push(dir);
	}

	void MouseBot::followPath(Path* path)
	{
		while (!path->empty())
		{
			DirectionVector dir = path->popStep();
			rotateToFaceDirection(dir.dir());
			for (int i = 0; i < dir.mag(); i++)
			{
				moveForward();
			}
		}
	}

	void MouseBot::backtrack()
	{
		direction dir = movementHistory.top();
		movementHistory.pop();
		rotateToFaceDirection(dir + S);
		moveForward();
		movementHistory.pop();
	}

	void MouseBot::moveForward()
	{
		move(facing);

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.moveForward();

#endif

	}

	void MouseBot::turnLeft()
	{
		facing = facing + NW;
		moveForward();
		facing = facing + NW;
	}

	void MouseBot::turnRight()
	{
		facing = facing + NE;
		moveForward();
		facing = facing + NE;
	}

	void MouseBot::rotateLeft()
	{
		facing = facing + W;

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.rotateLeft();

#endif
	}

	void MouseBot::rotateRight()
	{
		facing = facing + E;

#ifdef __MK20DX256__
		// If compiled for Teensy

		robotIO.rotateRight();

#endif
	}

	void MouseBot::rotateToFaceDirection(direction dir)
	{
		while (facing != dir)
		{
			direction temp = dir - facing;
			if (temp == NE || temp == E || temp == SE)
			{
				rotateRight();
			}
			else
			{
				rotateLeft();
			}
		}
	}
	
	
	
	
	
	bool isWallinDirection( direction dir )
	{
	    assert( dir == W || dir == N || dir == E || dir == NW || dir == NE );
	    
	    //TODO fill in distances will measured values
	    // distances now are just estimates
	    switch( dir )
	    {
	     case W:
	       return ( IRSensors[ LEFT ]->getDistance() < 100 );
	     break;
	     
	     case E:
	        return ( IRSensors[ RIGHT ]->getDistance() < 100 );
	     break;
	     
	     case N:
	        int dist1 = IRSensors[ FRONT_LEFT ]-.getDistance();
	        
	        return ( dist1 < 120 && abs( dist1 - IRSensors[ FRONT_RIGHT]->getDistance() ) < 30 );
	     break
	     
	     case NW:
	        int dist = IRSensors[ FRONT_LEFT ]->getDistance();
	        return ( dist < 150 && dist > 110 );
	     break;
	     
	     case NE:
            int dist = IRSensors[ FRONT_RIGHT ]->getDistance();
            return ( dist < 150 && dist > 110 );
         break;
	    }
	}
	
	
	
	
	
}

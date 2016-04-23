/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/



#include "MouseBot.h"
#include "Logger.h"



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

		logC(INFO) << "Randomly generated a virtual maze:\n";
		logC(INFO) << *virtualMaze << "\n";
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

	void MouseBot::mapMaze()
	{
		log(DEBUG1) << "Mapping Maze...";

		std::stack<PositionVector*> choicePositions = std::stack<PositionVector*>();
		choicePositions.push(new PositionVector(position));
		lookAround();
		
		while (!choicePositions.empty())
		{
			//logC(DEBUG1) << *maze;

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
#ifdef __MK20DX256__ // Teensy Compile
					digitalWrite(LED_PIN, LOW);
					delay(200);
					digitalWrite(LED_PIN, HIGH);
#endif
					choicePositions.push(new PositionVector(position));
				}

				direction dir = pickPossibleDirection();
				rotateToFaceDirection(dir);

				logC(DEBUG3) << "Traveled " << dir;

				moveForward(2);

				if (!maze->isExplored(position))
				{
					lookAround();
				}
			}
		}

		logC(INFO) << "Mapped maze:\n";

#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
		logC(INFO) << *maze;
#endif

		//temp for testing
		//Path * path2 = maze.findPath(PositionVector(0, 0), PositionVector(0, 0));
		/*Path * path = maze->findPath(PositionVector(0, 0), PositionVector(16, 16));
		for (int i = 0; i < path->size(); i++)
		{
			log(DEBUG2) << "Dir: " << path->peekStep().dir() << " Mag: " << path->peekStep().mag();
			path->popStep();
		}
		*/
	}



	void MouseBot::runMaze()
	{
		log(DEBUG1) << "Run Maze";

		followPath(maze->findPath(position, PositionVector(0 /*NUM_NODES_W / 2*/, 0 /*NUM_NODES_H / 2*/)));
		followPath(maze->findPath(position, PositionVector( /*NUM_NODES_W / 2*/16 , 16 /*NUM_NODES_H / 2*/)));
	}



	void MouseBot::returnToStart()
	{
	}



	void MouseBot::lookAround()
	{
		logC(DEBUG4) << "lookAround()";

		maze->addNode(position);
		maze->setOpen(true, position);
		maze->setExplored(true, position);

		if (isClearForward())
		{
			PositionVector pos = position + (facing + N);
			maze->setOpen(true, pos);
			maze->addNode(pos);
		}

		if (isClearRight())
		{
			PositionVector pos = position + (facing + E);
			maze->setOpen(true, pos);
			maze->addNode(pos);
		}

		if (isClearLeft())
		{
			PositionVector pos = position + (facing + W);
			maze->setOpen(true, pos);
			maze->addNode(pos);
		}

		maze->setExplored(true, position + (facing + N));
		maze->setExplored(true, position + (facing + E));
		maze->setExplored(true, position + (facing + W));
	}



	bool MouseBot::isPossibleDirection(direction dir)
	{
		logC(DEBUG4) << "isPossibleDirection()";

		return maze->isInsideMaze(position + dir) && maze->isOpen(position + dir) && !maze->isExplored((position + dir) + dir);
	}



	int MouseBot::numPossibleDirections()
	{
		logC(DEBUG4) << "numPossibleDirections()";

		int n = 0;

		if (isPossibleDirection(N)) n++;
		if (isPossibleDirection(E)) n++;
		if (isPossibleDirection(S)) n++;
		if (isPossibleDirection(W)) n++;

		return n;
	}



	direction MouseBot::pickPossibleDirection()
	{
		logC(DEBUG4) << "pickPossibleDirection()";

#ifdef __MK20DX256__ // Teensy Compile
		int rando = random(4);
#else // PC compile
		int rando = rand() % 4;
#endif

		switch (rando)
		{
		case 0:
			if (isPossibleDirection(N)) return N;
			if (isPossibleDirection(E)) return E;
			if (isPossibleDirection(S)) return S;
			if (isPossibleDirection(W)) return W;
		case 1:
			if (isPossibleDirection(E)) return E;
			if (isPossibleDirection(N)) return N;
			if (isPossibleDirection(S)) return S;
			if (isPossibleDirection(W)) return W;
		case 2:
			if (isPossibleDirection(W)) return W;
			if (isPossibleDirection(N)) return N;
			if (isPossibleDirection(E)) return E;
			if (isPossibleDirection(S)) return S;
		default:
			if (isPossibleDirection(E)) return E;
			if (isPossibleDirection(W)) return W;
			if (isPossibleDirection(N)) return N;
			if (isPossibleDirection(S)) return S;
		}

		return NONE;
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
		position = position + dir;
		movementHistory.push(dir);
	}



	void MouseBot::followPath(Path* path)
	{
		while (!path->empty())
		{
			DirectionVector dir = path->popStep();
			rotateToFaceDirection(dir.dir());
			moveForward(dir.mag());
		}
	}



	void MouseBot::backtrack()
	{
		direction dir = movementHistory.top();
		movementHistory.pop();
		rotateToFaceDirection(dir + S);
		moveForward(1);
		movementHistory.pop();
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





	void MouseBot::checkIRSensorRobotIO()
	{

		robotIO.checkIRSensors();
	}




	void MouseBot::checkMotorsRobotIO()
	{
		robotIO.checkMotors();
	}

	void MouseBot::checkGyroRobotIO()
	{
		robotIO.checkGyro();
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
}


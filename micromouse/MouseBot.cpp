/*********************************\
File:			MouseBot.cpp
Creation date:	3/2/2016
Author Name:	Joshua Murphy
Author GitHub:	joshuasrjc
\*********************************/

#include "MouseBot.h"

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	MouseBot::MouseBot()
	{
		setPos(PositionVector(0, 0));
		initSensors();
	}

	MouseBot::MouseBot(int x, int y)
	{
		setPos(PositionVector(x, y));
		initSensors();
	}

	MouseBot::MouseBot(PositionVector pos)
	{
		setPos(pos);
		initSensors();
	}

	MouseBot::~MouseBot()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}
	}

	/**** INITIALIZATIONS ****/

	void MouseBot::initSensors()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}

		IRSensors[LEFT] = new IRSenor(IR_LEFT_PIN, 40, 300);
		IRSensors[RIGHT] = new IRSenor(IR_RIGHT_PIN, 40, 300);
		IRSensors[FRONT_LEFT] = new IRSenor(IR_FRONT_LEFT_PIN, 40, 300);
		IRSensors[FRONT_RIGHT] = new IRSenor(IR_FRONT_RIGHT_PIN, 40, 300);
	}



	/**** SET / GET FUNCTIONS ****/

	PositionVector MouseBot::getPos()
	{
		return pos;
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
		this->pos = pos;
	}

	/**** MOVEMENT FUNCTIONS ****/

	void MouseBot::move(direction dir)
	{
		pos = pos + dir;
	}

	void MouseBot::moveForward()
	{
		move(facing);
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
	}

	void MouseBot::rotateRight()
	{
		facing = facing + E;
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

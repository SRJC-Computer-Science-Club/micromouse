#include "RobotIO.h"

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	RobotIO::RobotIO()
	{
		initSensors();
	}

	RobotIO::~RobotIO()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}
	}





	/**** SENSORS ****/

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearForward()
	{
		return false;
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearRight()
	{
		return false;
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearLeft()
	{
		return false;
	}

    
    
    bool isWallinDirection( direction dir )
    {
        throw exception();
        
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
    





	/**** MOTORS ****/

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::moveForward()
	{

	}

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::rotateLeft()
	{

	}

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::rotateRight()
	{

	}

    




	/**** INITIALIZATIONS ****/

	void RobotIO::initSensors()
	{
		IRSensors[LEFT] = new IRSenor(IR_LEFT_PIN, 40, 300);
		IRSensors[RIGHT] = new IRSenor(IR_RIGHT_PIN, 40, 300);
		IRSensors[FRONT_LEFT] = new IRSenor(IR_FRONT_LEFT_PIN, 40, 300);
		IRSensors[FRONT_RIGHT] = new IRSenor(IR_FRONT_RIGHT_PIN, 40, 300);
	}
}
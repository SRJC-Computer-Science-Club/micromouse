#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"

#ifdef __MK20DX256__ //this is the Teensy signature
// ### This line causes a lot of problems. It seems to conflict with #include <Encoder.h> ###
// ### I'm not sure what it's for, so for now it's commented out.
//#include <Arduino.h>//random
#endif

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
		return true;
		return !isWallinDirection(N);
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearRight()
	{
		return true;
		return !isWallinDirection(W);
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearLeft()
	{
		return true;
        return !isWallinDirection(E);
    }

    
    bool RobotIO::isWallinDirection( direction dir )
    {
        // insure valid data
        assert( dir == W || dir ==  N || dir == E || dir == NW || dir == NE);
        
        int numOpen = 0;
        
        for (int i = 0; i != 6; i++)
        {
            #ifdef __MK20DX256__ //this is the Teensy signature
            // TODO test for better intervol
            delay(1);
            #endif
            
            //TODO fill in distances will measured values
            // distances now are just estimates
            switch( dir )
            {
                
                case W:
                {
                    if  ( IRSensors[ LEFT ]->getDistance() < 100 )
                    {
                        numOpen++;
                    }
                    break;
                
                }
                
                case E:
                {
                    if ( IRSensors[ RIGHT ]->getDistance() < 100 )
                    {
                        numOpen++;
                    }
                    break;
                
                }
                
                case N:
                {
                    int dist = IRSensors[ FRONT_LEFT ]->getDistance();
                
                    if ( dist < 120 && abs( dist - IRSensors[ FRONT_RIGHT]->getDistance() ) < 30 )
                    {
                        numOpen++;
                    }
                    break;
                }
                
                case NW:
                {
                    int dist = IRSensors[ FRONT_LEFT ]->getDistance();
                    
                    if ( dist < 150 && dist > 110 )
                    {
                        numOpen++;
                    }
                    break;
                }
                case NE:
                {
                    int dist = IRSensors[ FRONT_RIGHT ]->getDistance();
                    
                    if ( dist < 150 && dist > 110 )
                    {
                        numOpen++;
                    }
                    break;
                }
				default:
					log(ERROR) << "NOT valid direction to check for wall";
					break;

            }
        }
        
        // TODO perfect the amount of tests and amount needed to give true.
        // if only 2 or less of the 6 wall tests came out true
		return numOpen > 2;    
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
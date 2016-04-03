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
		initPins();
		initIRSensors();

#ifdef __MK20DX256__
		rightMotor.setMaxSpeed(0.2f);
		leftMotor.setMaxSpeed(0.2f);
#endif
	}

	RobotIO::~RobotIO()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}
	}





	/**** SENSORS ****/

	bool RobotIO::isClearForward()
	{
		return !isWallinDirection(N);
	}

	bool RobotIO::isClearRight()
	{
		return !isWallinDirection(W);
	}

	bool RobotIO::isClearLeft()
	{
        return !isWallinDirection(E);
    }



	void RobotIO::followPath(Path * path)
	{
		// TODO implement

		delete path;
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
                    int dist = (int) IRSensors[ FRONT_LEFT ]->getDistance();

                    if ( dist < 120 && abs( dist - IRSensors[ FRONT_RIGHT]->getDistance() ) < 30 )
                    {
                        numOpen++;
                    }
                    break;
                }

                case NW:
                {
                    int dist = (int) IRSensors[ FRONT_LEFT ]->getDistance();

                    if ( dist < 150 && dist > 110 )
                    {
                        numOpen++;
                    }
                    break;
                }
                case NE:
                {
                    int dist = (int) IRSensors[ FRONT_RIGHT ]->getDistance();

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

	void RobotIO::testMotors()
	{
#ifdef __MK20DX256__
		rightMotor.setMaxSpeed(0.2f);
		leftMotor.setMaxSpeed(0.2f);

		rightMotor.setMovement(1.0f);
		delay(1000);
		rightMotor.brake();
		delay(1000);
		leftMotor.setMovement(1.0f);
		delay(1000);
		leftMotor.brake();
		delay(1000);
		rightMotor.setMovement(-1.0f);
		delay(1000);
		rightMotor.coast();
		delay(1000);
		leftMotor.setMovement(-1.0f);
		delay(1000);
		leftMotor.coast();
		delay(1000);

		rightMotor.setMaxSpeed(1.0f);
		leftMotor.setMaxSpeed(1.0f);

		leftMotor.setMovement(1.0f);
		rightMotor.setMovement(1.0f);
		delay(2000);
		leftMotor.brake();
		rightMotor.brake();
#endif
	}

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

	void RobotIO::initIRSensors()
	{
		IRSensors[LEFT] = new IRSenor(IR_LEFT_PIN, 20, 150);
		IRSensors[RIGHT] = new IRSenor(IR_RIGHT_PIN, 20, 150);
		IRSensors[FRONT_LEFT] = new IRSenor(IR_FRONT_LEFT_PIN, 20, 150);
		IRSensors[FRONT_RIGHT] = new IRSenor(IR_FRONT_RIGHT_PIN, 20, 150);
	}

	void RobotIO::initPins()
	{
#ifdef __MK20DX256__ // Teensy compile
		pinMode(BUTTON_PIN, INPUT_PULLUP);
		pinMode(SWITCH_A_PIN, INPUT_PULLUP);
		pinMode(SWITCH_B_PIN, INPUT_PULLUP); 
		pinMode(SWITCH_C_PIN, INPUT_PULLUP);
#endif
	}

	void RobotIO::calibrateIRSensors()
	{
		IRSensors[LEFT]->calibrate(20, 20);
		IRSensors[RIGHT]->calibrate(20, 20);
		IRSensors[FRONT_LEFT]->calibrate(20, 20);
		IRSensors[FRONT_RIGHT]->calibrate(20, 20);
	}
}

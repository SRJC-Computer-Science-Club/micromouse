#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"
#include "PIDController"

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
#ifdef __MK20DX256__
		pinMode(BUTTON_PIN, INPUT);
#endif

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
	void RobotIO::moveForward(int node)
	{
		#ifdef __MK20DX256__
		PIDController pidcontroller;
		int countsNeeded=node*4807;
		float leftmotorValue;
		float rightmotorValue;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);


//This is the fast run portion of the path. the mouse will move as fast as it can until it reach
// 90% of the path then it will enter the slow run until the destination
		while (rightmotor.getCounts<0.9*countsNeeded||leftMotor.getCounts<0.9*countsNeeded)
		{
			//This slowes down the top speed when it getts close to the target
			//since we dont want to over shoot
			if(rightrightmotor.getCounts>0.9*countsNeeded||leftMotor.getCounts>0.9*countsNeeded)
			{
				leftMotor.setMaxSpeed(0.2f);
				rightMotor.setMaxSpeed(0.2f);
			}
			leftmotorValue=1;
			rightmotorValue=1;

			if (!isClearRight() && IRSensors[RIGHT].getDistance()>50)
			{
				rightmotorValue+=pidcontroller.getCorrection(40-IRSensors[RIGHT].getDistance());
				rightMotor.setMovement(rightmotorValue);
			}
			else if(!isClearRight() && IRSensors[RIGHT].getDistance()<30)
			{
				leftmotorValue+=pidcontroller.getCorrection(IRSensors[RIGHT].getDistance()-40);
				leftMotor.setMovement(leftmotorValue);

			}
			else if (!isClearLeft() && IRSensors[RIGHT].getDistance()>50)
			{
				leftmotorValue+=pidcontroller.getCorrection(40-IRSensors[LEFT].getDistance());
				leftMotor.setMovement(leftmotorValue);

			}
			else if(!isClearLeft() &&  IRSensors[RIGHT].getDistance()<30)
			{
				leftmotorValue+=pidcontroller.getCorrection(40-IRSensors[LEFT].getDistance());
				leftMotor.setMovement(leftmotorValue);

			}

		}



		leftMotor.brake();
		rightMotor.brake();

#endif

	}

	// ## NOT YET IMPLEMENTED ##
	void RobotIO::rotateLeft()
	{
		#ifdef __MK20DX256__
		PIDController pidcontroller;
		float leftmotorValue=-1.0f;
		float rightmotorValue=1.0f;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);
		//TODO include gyro information. declar gyro information


		while(false/*magnito motor value != 90*/)
		{
			if(/*magnitometer value >80*/)
			{
				leftMotor.setMaxSpeed(0.2f);
				rightMotor.setMaxSpeed(0.2f);
			}
			leftMotor.setMovement(leftmotorValue);
			rightMotor.setMovment(rightmotorValue);
		}

		rightMotor.brake();
		leftMotor.brake();

		#endif
	}

	// ## NOT YET IMPLEMENTED ##
	void RobotIO::rotateRight()
	{
		#ifdef __MK20DX256__
		PIDController pidcontroller;
		float leftmotorValue=1.0f;
		float rightmotorValue=-1.0f;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);
		//TODO include gyro information. declar gyro information


		while(false/*magnito motor value != 90*/)
		{
			if(/*magnitometer value >80*/)
		{
			leftMotor.setMaxSpeed(0.2f);
			rightMotor.setMaxSpeed(0.2f);
		}
			leftMotor.setMovement(leftmotorValue);
			rightMotor.setMovment(rightmotorValue);
		}

		rightMotor.brake();
		leftMotor.brake();

		#endif

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

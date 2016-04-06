#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"
#include "PIDControl.h"
#include "MouseBot.h"

#ifdef __MK20DX256__ //this is the Teensy signature
// ### This line causes a lot of problems. It seems to conflict with #include <Encoder.h> ###
// ### I'm not sure what it's for, so for now it's commented out.
//#include <Arduino.h>//random
#endif

namespace Micromouse
{
#ifndef __MK20DX256__
	void delay(int n) {}
#endif

	/**** CONSTRUCTORS ****/

	RobotIO::RobotIO()
	{
        #ifdef __MK20DX256__
		pinMode(BUTTON_PIN, INPUT);
        
        #endif
		initPins();
		initIRSensors();
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
	}

	// ## NOT YET IMPLEMENTED ##
	void RobotIO::moveForward(float node)
	{
		int countsNeeded=node*4807;
		float leftmotorValue;
		float rightmotorValue;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);


        //This is the fast run portion of the path. the mouse will move as fast as it can until it reach
        // 90% of the path then it will enter the slow run until the destination
		while (rightMotor.getCounts() < countsNeeded || leftMotor.getCounts() < countsNeeded)
		{
			//This slowes down the top speed when it getts close to the target
			//since we dont want to over shoot
			if(rightMotor.getCounts() > 0.9f*countsNeeded || leftMotor.getCounts() > 0.9f*countsNeeded)
			{
				leftMotor.setMaxSpeed(0.2f);
				rightMotor.setMaxSpeed(0.2f);
			}
			leftmotorValue=1;
			rightmotorValue=1;

			if (!isClearRight() && IRSensors[RIGHT]->getDistance()>50)
			{
				rightmotorValue+=pidcontroller.getCorrection(40-IRSensors[RIGHT]->getDistance());
				rightMotor.setMovement(rightmotorValue);
			}
			else if(!isClearRight() && IRSensors[RIGHT]->getDistance()<30)
			{
				leftmotorValue+=pidcontroller.getCorrection(IRSensors[RIGHT]->getDistance()-40);
				leftMotor.setMovement(leftmotorValue);

			}
			else if (!isClearLeft() && IRSensors[RIGHT]->getDistance()>50)
			{
				leftmotorValue+=pidcontroller.getCorrection(40-IRSensors[LEFT]->getDistance());
				leftMotor.setMovement(leftmotorValue);

			}
			else if(!isClearLeft() &&  IRSensors[RIGHT]->getDistance()<30)
			{
				leftmotorValue+=pidcontroller.getCorrection(40-IRSensors[LEFT]->getDistance());
				leftMotor.setMovement(leftmotorValue);

			}

		}



		leftMotor.brake();
		rightMotor.brake();

	}


	// ## NOT YET IMPLEMENTED ##
	void RobotIO::rotateLeft()
	{
		float leftmotorValue=-1.0f;
		float rightmotorValue=1.0f;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);
		//TODO include gyro information. declar gyro information


		while(false/*magnito motor value != 90*/)
		{
			if(false/*magnitometer value >80*/)
			{
				leftMotor.setMaxSpeed(0.2f);
				rightMotor.setMaxSpeed(0.2f);
			}
			leftMotor.setMovement(leftmotorValue);
			rightMotor.setMovement(rightmotorValue);
		}

		rightMotor.brake();
		leftMotor.brake();
	}

	// ## NOT YET IMPLEMENTED ##
	void RobotIO::rotateRight()
	{
		float leftmotorValue=1.0f;
		float rightmotorValue=-1.0f;
		rightMotor.resetCounts();
		leftMotor.resetCounts();
		leftMotor.setMaxSpeed(1.0f);
		rightMotor.setMaxSpeed(1.0f);
		//TODO include gyro information. declar gyro information


		while(false/*magnito motor value != 90*/)
		{
			if(false/*magnitometer value >80*/)
		{
			leftMotor.setMaxSpeed(0.2f);
			rightMotor.setMaxSpeed(0.2f);
		}
			leftMotor.setMovement(leftmotorValue);
			rightMotor.setMovement(rightmotorValue);
		}

		rightMotor.brake();
		leftMotor.brake();
	}





    // ## NOT YET IMPLEMENTED ##
    void RobotIO::followPath(Path path)
    {
        assert(path.empty());
        //TODO I am assuming that the micromouse is looking in the direction
        //of the first Path

        
        while(!path.empty())
        {
        rotateTo(path.peekStep().dir());
		moveForward(path.popStep().mag());

        }

    }




    // ## NOT YET IMPLEMENTED ##
    void RobotIO::rotateTo(direction dir)
    {
   
    }




	/**** INITIALIZATIONS ****/

	void RobotIO::initIRSensors()
	{
		IRSensors[LEFT] = new IRSenor(IR_LEFT_PIN, 20, 150);
		IRSensors[RIGHT] = new IRSenor(IR_RIGHT_PIN, 20, 150);
		IRSensors[FRONT_LEFT] = new IRSenor(IR_FRONT_LEFT_PIN, 20, 150);
		IRSensors[FRONT_RIGHT] = new IRSenor(IR_FRONT_RIGHT_PIN, 20, 150);

		//TODO check if load fails
		IRSensors[LEFT]->loadCalibration(IR_LEFT_MEMORY);
		IRSensors[RIGHT]->loadCalibration(IR_RIGHT_MEMORY);
		IRSensors[FRONT_LEFT]->loadCalibration(IR_FRONT_LEFT_MEMORY);
		IRSensors[FRONT_RIGHT]->loadCalibration(IR_FRONT_RIGHT_MEMORY);


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

		//TODO check if calibrations were good/ ask to save
		IRSensors[LEFT]->saveCalibration(IR_LEFT_MEMORY);
		IRSensors[RIGHT]->saveCalibration(IR_RIGHT_MEMORY);
		IRSensors[FRONT_LEFT]->saveCalibration(IR_FRONT_LEFT_MEMORY);
		IRSensors[FRONT_RIGHT]->saveCalibration(IR_FRONT_RIGHT_MEMORY);


	}
}

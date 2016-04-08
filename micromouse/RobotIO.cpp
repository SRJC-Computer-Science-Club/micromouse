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
#define PI (3.141592f)

	/**** CONSTRUCTORS ****/

	RobotIO::RobotIO()
	{
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



	float RobotIO::estimateHeadingError()
	{
		float rightDist = IRSensors[RIGHT]->getDistance();
		float leftDist = IRSensors[LEFT]->getDistance();
		bool rightWall = leftDist < WALL_DISTANCE * 1.25f;
		bool leftWall = rightDist < WALL_DISTANCE * 1.25f;

		if (rightWall && leftWall)
		{
			return leftDist - rightDist;
		}
		else if (rightWall && !leftWall)
		{
			return 2 * (WALL_DISTANCE - rightDist);
		}
		else if (leftWall && !rightWall)
		{
			return 2 * (leftDist - WALL_DISTANCE);
		}
		else // (!rightWall && !leftWall)
		{
			// TODO: Use magnetometer
			return 0.0f;
		}
	}








	/**** MOTORS ****/

	void RobotIO::testMotors()
	{
		moveForward(180.0f);
/*
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
*/

	}



	void RobotIO::moveForward(float millimeters)
	{
		//centimeters represents how much farther the bot needs to travel.
		//The function will loop until centimeters is within DISTANCE_TOLERANCE

		PIDController distPID = PIDController(15.0f, 5.0f, 0.25f);
		PIDController headingPID = PIDController(1, 1, 1);

		leftMotor.setMaxSpeed(0.25f);
		rightMotor.setMaxSpeed(0.25f);
		leftMotor.resetCounts();
		rightMotor.resetCounts();

		distPID.start(millimeters);
		headingPID.start(estimateHeadingError());

		while (millimeters > DISTANCE_TOLERANCE || millimeters < -DISTANCE_TOLERANCE)
		{

			//Get distance traveled in cm since last cycle (average of two encoders)
			float traveled = leftMotor.resetCounts() + rightMotor.resetCounts(); //resetCounts() also returns counts
			traveled /= 2;
			traveled /= COUNTS_PER_MM;

			//Decrease distance to go by the estimated amount traveled
			millimeters -= traveled;

			//Get correction speed
			float speed = distPID.getCorrection(millimeters);

			//Get rotational correction speed
			float rotSpeed = headingPID.getCorrection(estimateHeadingError());

			//Disables heading correction.
			rotSpeed = 0.0f;

			if (rotSpeed < 0)
			{
				//Move forward while turning right.
				rightMotor.setMovement(speed * (1.0f + 2 * rotSpeed));

				leftMotor.setMovement(speed);
			}
			else
			{
				//Move forward while turning left.
				leftMotor.setMovement(speed * (1.0f - 2 * rotSpeed));

				rightMotor.setMovement(speed);
			}
		}

		leftMotor.brake();
		rightMotor.brake();
	}


	void RobotIO::rotate(float degrees)
	{
		PIDController anglePID = PIDController(15.0f, 5.0f, 0.25f);
		anglePID.start(degrees);
		float angleCorrection = anglePID.getCorrection(degrees);

		leftMotor.resetCounts();
		rightMotor.resetCounts();

		while (degrees > ANGLE_TOLERANCE || degrees < -ANGLE_TOLERANCE || angleCorrection > 0.1f)
		{
			int counts = (leftMotor.resetCounts() - rightMotor.resetCounts()) / 2;
			degrees -= counts / COUNTS_PER_MM / (MM_BETWEEN_WHEELS/2) * (180/PI);

			angleCorrection = anglePID.getCorrection(degrees);

			leftMotor.setMovement(angleCorrection);
			rightMotor.setMovement(angleCorrection);
		}

		leftMotor.brake();
		rightMotor.brake();
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

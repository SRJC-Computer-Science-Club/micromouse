#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"
#include "Timer.h"

#ifdef __MK20DX256__ //this is the Teensy signature
// ### This line causes a lot of problems. It seems to conflict with #include <Encoder.h> ###
// ### I'm not sure what it's for, so for now it's commented out.
//#include <Arduino.h>//random
#endif

namespace Micromouse
{
#ifndef __MK20DX256__
#define PI (3.141592f) //Already defined on Arduino
#endif


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
		return !isWallinDirection(E);
	}



	bool RobotIO::isClearLeft()
	{
        return !isWallinDirection(W);
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
        #ifdef __MK20DX256__ //this is the Teensy signature
        // TODO test for better intervol
        #endif

        //TODO fill in distances will measured values
        // distances now are just estimates
        switch( dir )
        {

            case W:
            {
				return IRSensors[LEFT]->getDistance() < 100;
            }

            case E:
            {
				return IRSensors[RIGHT]->getDistance() < 100;
            }

            case N:
            {
                int dist = (int) IRSensors[ FRONT_LEFT ]->getDistance();
				return (dist < 120 && abs(dist - IRSensors[FRONT_RIGHT]->getDistance()) < 30);
            }

			default:
				log(ERROR) << "NOT valid direction to check for wall";
				break;
		}
    }



	float RobotIO::estimateHeadingError()
	{
		float rightDist = IRSensors[RIGHT]->getDistance();
		float leftDist = IRSensors[LEFT]->getDistance();
		bool rightWall = leftDist < WALL_DISTANCE * 1.85f;
		bool leftWall = rightDist < WALL_DISTANCE * 1.85f;

		if (rightWall && leftWall)
		{
			return (leftDist - rightDist);
		}
		else if (rightWall && !leftWall)
		{
			//return (WALL_DISTANCE - rightDist);
			return 0;
		}
		else if (leftWall && !rightWall)
		{
			//return (leftDist - WALL_DISTANCE);
			return 0;
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
#ifdef __MK20DX256__
		//rotate(90.0f);
		//delay(2000);
		moveForward(180.0f);
		moveForward(180.0f);
		moveForward(180.0f);
		moveForward(180.0f);
		moveForward(180.0f);
		moveForward(180.0f);
		moveForward(180.0f);
/*
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
		*/
#endif


	}

	void RobotIO::testIR()
	{
		//IRSensors[RIGHT]->calibrate(20, 20);
		//IRSensors[RIGHT]->saveCalibration(IR_RIGHT_MEMORY);

		//IRSensors[LEFT]->calibrate(20, 20);
		//IRSensors[LEFT]->saveCalibration(IR_LEFT_MEMORY);

	//	IRSensors[LEFT]->calibrate(20, 20);
	//	IRSensors[LEFT]->saveCalibration(IR_FRONT_LEFT_MEMORY);


		for (int i = 0; i < 2000; i++)
		{
			logC(INFO) << "FWD RIGHT:  " << IRSensors[FRONT_RIGHT]->getDistance();
			logC(INFO) << "FWD LEFT:   " << IRSensors[FRONT_LEFT]->getDistance();
			//IRSensors[FRONT_LEFT]->debug();
			//IRSensors[FRONT_RIGHT]->debug();
#ifdef __MK20DX256__ //Teensy
			delay(200);
#endif


		}
	}


	void RobotIO::moveForward(float millimeters)
	{
		//centimeters represents how much farther the bot needs to travel.
		//The function will loop until centimeters is within DISTANCE_TOLERANCE

		float leftmm = millimeters;
		float rightmm = millimeters;

		PIDController leftDistPID = PIDController(97.0f, 42.0f, 14.0f);
		PIDController rightDistPID = PIDController(97.0f, 42.0f, 14.0f);

		PIDController speedPID = PIDController(30.0f, 1.0f, 1.0f);

		PIDController headingPID = PIDController(0.4f, 0.01f, 0.2f);

		//leftMotor.setMaxSpeed(.2125f);
		leftMotor.setMaxSpeed(.17f);
		rightMotor.setMaxSpeed(.16f);
		leftMotor.resetCounts();
		rightMotor.resetCounts();


		leftDistPID.start(millimeters);
		rightDistPID.start(millimeters);
		speedPID.start(0);
		headingPID.start(estimateHeadingError());

		float leftSpeed = 1.0f;
		float rightSpeed = 1.0f;

		float frontLeftIRDist = 200.0f;
		float frontRightIRDist = 200.0f;

		Timer timer;

		while
			((
				leftmm > DISTANCE_TOLERANCE || leftmm < -DISTANCE_TOLERANCE ||
				rightmm > DISTANCE_TOLERANCE || rightmm < -DISTANCE_TOLERANCE ||
				leftSpeed > 0.2f || rightSpeed > 0.2f
				)&&(frontLeftIRDist > FRONT_LEFT_WALL_DISTANCE || frontRightIRDist > FRONT_RIGHT_WALL_DISTANCE)
				&&(frontLeftIRDist > 20.0f && frontRightIRDist > 20.0f)
				)
		{
			float deltaTime = timer.getDeltaTime();

			//Get distance from the front of the bot to the wall.
			frontRightIRDist = IRSensors[FRONT_RIGHT]->getDistance();
			frontLeftIRDist = IRSensors[FRONT_LEFT]->getDistance();

			//Get distance traveled in cm since last cycle (average of two encoders)
			float leftTraveled = leftMotor.resetCounts();
			float rightTraveled = rightMotor.resetCounts();
			leftTraveled /= COUNTS_PER_MM;
			rightTraveled /= COUNTS_PER_MM;

			float actualLeftSpeed = leftTraveled / deltaTime;
			float actualRightSpeed = rightTraveled / deltaTime;

			//Decrease distance to go by the estimated amount traveled
			leftmm -= leftTraveled;
			rightmm -= rightTraveled;

			leftSpeed = leftDistPID.getCorrection(leftmm);
			rightSpeed = rightDistPID.getCorrection(rightmm);

			float speedError = actualLeftSpeed - actualRightSpeed;
			float speedCorrection = speedPID.getCorrection(speedError);
			//speedCorrection *= -1;

			//logC(INFO) << speedCorrection;

			if (rightSpeed < 0.25f || leftSpeed < 0.25f)
			{
				speedCorrection = 0.0f;
			}

			if (speedCorrection < 0)
			{
				rightSpeed += speedCorrection;
			}
			else
			{
				leftSpeed -= speedCorrection;
			}

			//Get rotational correction speed
			float rotError = estimateHeadingError();
			//logC(DEBUG1) << "Rotational Error: " << rotError;
			float rotSpeed = headingPID.getCorrection(rotError);

			//Disables heading correction.
			rotSpeed = 0.0f;

			//Move forward while turning right.

			if (rotSpeed < 0)
			{
				float c = (1 + 3 * rotSpeed);
				c < 0.75 ? 0.75 : c;
				rightSpeed *= c; //cos(PI * rotSpeed);
			}
			else
			{
				float c = (1 - 3 * rotSpeed);
				c < 0.75 ? 0.75 : c;
				leftSpeed *= c; //cos(PI * rotSpeed);
			}

			rightMotor.setMovement(rightSpeed);
			leftMotor.setMovement(leftSpeed);
		}

		logC(INFO) << leftDistPID.getI();
		logC(INFO) << rightDistPID.getI();

		leftMotor.brake();
		rightMotor.brake();
	}

	void RobotIO::testRotate()
	{
		rotate(180);
#ifdef __MK20DX256__ //Teensy
		delay(1000);
#endif
		rotate(-180);
#ifdef __MK20DX256__ //Teensy
		delay(1000);
#endif
		rotate(90);
#ifdef __MK20DX256__ //Teensy
		delay(1000);
#endif
		rotate(-90);

#ifdef __MK20DX256__ //Teensy
		delay(1000);
#endif
		rotate(45);

#ifdef __MK20DX256__ //Teensy
		delay(1000);
#endif
		rotate(-45);

	}


	void RobotIO::rotate(float degrees)
	{

		leftMotor.setMaxSpeed(0.16f);
		rightMotor.setMaxSpeed(0.16f);

		PIDController speedPID = PIDController(30.f, 2.0f, 1.0f , 100.0f);

		PIDController anglePID = PIDController(150.0f, 75.0f , 10.0f, 20.0f);


		anglePID.start(degrees);
		speedPID.start(0);
		float angleCorrection = anglePID.getCorrection(degrees);

		leftMotor.resetCounts();
		rightMotor.resetCounts();

		float leftTraveled;
		float rightTraveled;

		float deltaTime;

		float actualLeftSpeed;
		float actualRightSpeed;

		float rightSpeed, leftSpeed;
		

		Timer timer;
		while (degrees > ANGLE_TOLERANCE || degrees < -ANGLE_TOLERANCE || angleCorrection > 0.1f)
		{
#ifdef __MK20DX256__ //Teensy
			delayMicroseconds(2000);
#endif
			leftTraveled = leftMotor.resetCounts();
			rightTraveled = rightMotor.resetCounts();
			deltaTime = timer.getDeltaTime();

			int counts = (leftTraveled - rightTraveled) / 2;
			degrees -= counts * (180 / PI) / COUNTS_PER_MM / (MM_BETWEEN_WHEELS/2);
			leftTraveled /= COUNTS_PER_MM;
			rightTraveled /= COUNTS_PER_MM;


			actualLeftSpeed = leftTraveled / deltaTime;
			actualRightSpeed = rightTraveled / deltaTime;



			angleCorrection = anglePID.getCorrection(degrees);


			leftSpeed = -angleCorrection;
			rightSpeed = angleCorrection;

			float speedCorrection = speedPID.getCorrection( actualRightSpeed - actualLeftSpeed );
			//speedCorrection = 0;
			if (rightSpeed < 0.25f || leftSpeed < 0.25f)
			{
				speedCorrection = 0.0f;
			}

			if (speedCorrection < 0)
			{
				rightSpeed += speedCorrection;
			}
			else
			{
				leftSpeed -= speedCorrection;
			}

			leftMotor.setMovement(rightSpeed);
			rightMotor.setMovement(leftSpeed);


			//logC(INFO) << degrees;
		}

		logC(INFO) << anglePID.getI();

		leftMotor.brake();
		rightMotor.brake();
	}








	/**** INITIALIZATIONS ****/

	void RobotIO::initIRSensors()
	{
		IRSensors[LEFT] = new IRSensor(IR_LEFT_PIN, 20, 150);
		IRSensors[RIGHT] = new IRSensor(IR_RIGHT_PIN, 20, 150);
		IRSensors[FRONT_LEFT] = new IRSensor(IR_FRONT_LEFT_PIN, 20, 150);
		IRSensors[FRONT_RIGHT] = new IRSensor(IR_FRONT_RIGHT_PIN, 20, 150);


		//TODO check if load fails
#ifdef __MK20DX256__ // Teensy compile
		delay(300);
#endif


		log(DEBUG3) << "Load right";
		IRSensors[RIGHT]->loadCalibration(IR_RIGHT_MEMORY);//todo change back

#ifdef __MK20DX256__ // Teensy compile
		delay(300);
#endif

		log(DEBUG3) << "Load left";
		IRSensors[LEFT]->loadCalibration(IR_LEFT_MEMORY);

#ifdef __MK20DX256__ // Teensy compile
		delay(300);
#endif

		log(DEBUG3) << "Load front right";
		IRSensors[FRONT_RIGHT]->loadCalibration(IR_LEFT_MEMORY);

#ifdef __MK20DX256__ // Teensy compile
		delay(300);
#endif

		log(DEBUG3) << "Load front left";
		IRSensors[FRONT_LEFT]->loadCalibration(IR_LEFT_MEMORY);

#ifdef __MK20DX256__ // Teensy compile
		delay(300);
#endif

		//IRSensors[FRONT_LEFT]->loadCalibration(IR_FRONT_LEFT_MEMORY);
		//IRSensors[FRONT_RIGHT]->loadCalibration(IR_FRONT_RIGHT_MEMORY);

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

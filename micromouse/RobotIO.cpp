#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"
#include "Timer.h"



#ifdef __MK20DX256__ // Teensy Compile
// ### This line causes a lot of problems. It seems to conflict with #include <Encoder.h> ###
// ### I'm not sure what it's for, so for now it's commented out.
//#include <Arduino.h>//random
#endif



#ifdef __MK20DX256__ // Teensy compile
#else // PC compile
	#define PI (3.141592f) //Already defined on Arduino
#endif



namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	RobotIO::RobotIO()
	{
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
        // ensure valid data
        assert( dir == W || dir ==  N || dir == E || dir == NW || dir == NE);

        switch( dir )
        {
        case W:
			return IRSensors[LEFT]->getDistance() < 110;

        case E:
			return IRSensors[RIGHT]->getDistance() < 110;

        case N:
		{
			int dist = (int)IRSensors[FRONT_LEFT]->getDistance();

			return (dist < 120 && abs(dist - IRSensors[FRONT_RIGHT]->getDistance()) < 30); 
		}

		default:
			log(ERROR) << "NOT valid direction to check for wall";
			return false;
		}
    }



	float RobotIO::estimateHeadingError()
	{
		float rightDist = IRSensors[RIGHT]->getDistance();
		float leftDist = IRSensors[LEFT]->getDistance();

		float frontLeftDist = IRSensors[FRONT_LEFT]->getDistance();
		float frontRightDist = IRSensors[FRONT_RIGHT]->getDistance();

		bool rightWall = leftDist < WALL_DISTANCE * 1.85f;
		bool leftWall = rightDist < WALL_DISTANCE * 1.85f;

		bool frontLeftWall = frontLeftDist < FRONT_LEFT_WALL_DISTANCE;
		bool frontRightWall = frontRightDist < FRONT_RIGHT_WALL_DISTANCE;


		if (frontLeftWall && !frontRightWall)
		{
			//return -4.0f;
		}
		else if (frontRightWall && frontLeftWall)
		{
			//return 4.0f;
		}

		if (rightWall && leftWall)
		{
			return (leftDist - rightDist);
		}
		else if (rightWall && !leftWall)
		{
			float error = WALL_DISTANCE - rightDist;
			return error > 0 ? error : 0;
			return 0;
		}
		else if (leftWall && !rightWall)
		{
			float error = leftDist - WALL_DISTANCE;
			return error < 0 ? error : 0;
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
#ifdef __MK20DX256__ // Teensy Compile
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
		//IRSensors[FRONT_RIGHT]->calibrate(20, 20);
		//IRSensors[FRONT_RIGHT]->saveCalibration(IR_FRONT_RIGHT_MEMORY);

		//IRSensors[FRONT_LEFT]->calibrate(20, 20);
		//IRSensors[FRONT_LEFT]->saveCalibration(IR_FRONT_LEFT_MEMORY);

		//IRSensors[LEFT]->calibrate(20, 20);
		//IRSensors[LEFT]->saveCalibration(IR_FRONT_LEFT_MEMORY);


		for (int i = 0; i < 2000; i++)
		{
			logC(INFO) << "FWD RIGHT:  " << IRSensors[RIGHT]->getDistance();
			logC(INFO) << "FWD LEFT:   " << IRSensors[LEFT]->getDistance();
			//IRSensors[FRONT_LEFT]->debug();
			//IRSensors[FRONT_RIGHT]->debug();
#ifdef __MK20DX256__ // Teensy Compile
			delay(200);
#endif
		}
	}



	void RobotIO::moveForward(float millimeters)
	{
		//millimeters represents how much farther the bot needs to travel.
		//The function will loop until centimeters is within DISTANCE_TOLERANCE

		float leftmm = millimeters;
		float rightmm = millimeters;

		PIDController leftDistPID = PIDController(97.0f, 46.0f, 16.0f , 1000);
		PIDController rightDistPID = PIDController(97.0f, 46.0f, 16.0f , 1000);

		PIDController speedPID = PIDController(30.0f, 1.0f, 1.0f);

		PIDController headingPID = PIDController(0.5f, 0.01f, 0.2f);
		//PIDController headingPID = PIDController(0.5f, 0.04f, 0.02f , 250.0f); i want to try this one
		//PIDController headingPID = PIDController(1.2f, 0.03f, 0.15f,250.0f);

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
			(
				leftmm > DISTANCE_TOLERANCE || leftmm < -DISTANCE_TOLERANCE ||
				rightmm > DISTANCE_TOLERANCE || rightmm < -DISTANCE_TOLERANCE ||
				leftSpeed > 0.1f || rightSpeed > 0.1f
			)
		{
			BUTTONFLAG
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
			//rotSpeed = 0.0f;

			//Move forward while turning right.

			if (rotSpeed < 0)
			{
				float c = (1 + 3 * rotSpeed);
				c < 0.65 ? 0.65 : c;
				rightSpeed *= c; //cos(PI * rotSpeed);
			}
			else
			{
				float c = (1 - 3 * rotSpeed);
				c < 0.65 ? 0.65 : c;
				leftSpeed *= c; //cos(PI * rotSpeed);
			}

			rightMotor.setMovement(rightSpeed);
			leftMotor.setMovement(leftSpeed);
		}

		logC(INFO) << leftDistPID.getI();
		logC(INFO) << rightDistPID.getI();
		
		BUTTONEXIT;

		leftMotor.brake();
		rightMotor.brake();

	}



	void RobotIO::testRotate()
	{
		rotate(180);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(-180);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(90);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(-90);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(45);

#ifdef __MK20DX256__ // Teensy Compile
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

		float leftTraveled, rightTraveled;

		float deltaTime;

		float actualLeftSpeed, actualRightSpeed;

		float rightSpeed, leftSpeed;
		
		Timer timer;

		while (degrees > ANGLE_TOLERANCE || degrees < -ANGLE_TOLERANCE || angleCorrection > 0.1f)
		{
#ifdef __MK20DX256__ // Teensy Compile
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
#ifdef __MK20DX256__ // Teensy Compile
		delay(100);
#endif


		log(DEBUG3) << "Load right";
		IRSensors[RIGHT]->loadCalibration(IR_RIGHT_MEMORY);//todo change back

#ifdef __MK20DX256__ // Teensy Compile
		delay(20);
#endif

		log(DEBUG3) << "Load left";
		IRSensors[LEFT]->loadCalibration(IR_LEFT_MEMORY);

#ifdef __MK20DX256__ // Teensy Compile
		delay(20);
#endif

		log(DEBUG3) << "Load front right";
		IRSensors[FRONT_RIGHT]->loadCalibration(IR_FRONT_RIGHT_MEMORY);

#ifdef __MK20DX256__ // Teensy Compile
		delay(20);
#endif

		log(DEBUG3) << "Load front left";
		IRSensors[FRONT_LEFT]->loadCalibration(IR_FRONT_LEFT_MEMORY);


		//IRSensors[FRONT_LEFT]->loadCalibration(IR_FRONT_LEFT_MEMORY);
		//IRSensors[FRONT_RIGHT]->loadCalibration(IR_FRONT_RIGHT_MEMORY);
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

#include "RobotIO.h"
#include "IRSensor.h"
#include "Vector.h"
#include "Logger.h"
#include "Timer.h"
#include "ButtonFlag.h"
#include "Recorder.h"
#include "ArduinoDummy.h"



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
			return irDistances[LEFT] < 110;

        case E:
			return irDistances[RIGHT] < 110;

        case N:
		{
			return irDistances[FRONT_LEFT] < 55 && irDistances[FRONT_RIGHT] < 55;
		}

		default:
			log(ERROR) << "NOT valid direction to check for wall";
			return false;
		}
    }



	void RobotIO::updateIRDistances()
	{
		float samples[N_IR_SENSORS][IR_SAMPLE_SIZE];
		float averages[N_IR_SENSORS];

		for (int a = 0; a < IR_SAMPLE_SIZE; a++)
		{
			for (int n = 0; n < N_IR_SENSORS; n++)
			{
				samples[n][a] = IRSensors[n]->getDistance();
				averages[n] += samples[n][a];
			}
		}

		for (int n = 0; n < N_IR_SENSORS; n++)
		{
			averages[n] /= 2;
		}

		float smallestDistsToAvg[N_IR_SENSORS];
		float closestSamples[N_IR_SENSORS];

		for (int n = 0; n < N_IR_SENSORS; n++)
		{
			smallestDistsToAvg[n] = std::numeric_limits<float>::infinity();
		}

		for (int a = 0; a < IR_SAMPLE_SIZE; a++)
		{
			for (int n = 0; n < N_IR_SENSORS; n++)
			{
				float distToAvg = abs(samples[n][a]);
				if (distToAvg < smallestDistsToAvg[n])
				{
					smallestDistsToAvg[n] = distToAvg;
					closestSamples[n] = samples[n][a];
				}
			}
		}

		for (int n = 0; n < N_IR_SENSORS; n++)
		{
			irDistances[n] = closestSamples[n];
		}
	}



	void RobotIO::printIRDistances()
	{
		updateIRDistances();
		float total = irDistances[LEFT] + irDistances[RIGHT];
		float left = irDistances[LEFT];
		while (true)
		{
			BUTTONFLAG;
			//Timer::sleep(0.1);
			updateIRDistances();
			total = 0.99f * total + 0.01f * (irDistances[LEFT] + irDistances[RIGHT]);
			left = 0.9f * left + 0.1f * irDistances[LEFT];
			for (int n = 0; n < N_IR_SENSORS; n++)
			{
				Serial.print(irDistances[n], 4);
				Serial.print(", ");
			}
			Serial.print(left, 4);
			Serial.print(", ");
			Serial.println(total, 4);
		}

		BUTTONEXIT;

		return;
	}








	/**** MOTORS ****/

	void RobotIO::testMotors()
	{
		moveForward(10.0f * 180.0f, true);
		rotate(180.0f);
		moveForward(10.0f * 180.0f, true);
		leftMotor.brake();
		rightMotor.brake();
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
			BUTTONFLAG

			logC(INFO) << "FWD RIGHT:  " << IRSensors[RIGHT]->getDistance();
			logC(INFO) << "FWD LEFT:   " << IRSensors[LEFT]->getDistance();
			//IRSensors[FRONT_LEFT]->debug();
			//IRSensors[FRONT_RIGHT]->debug();
#ifdef __MK20DX256__ // Teensy Compile
			delay(200);
#endif
		}

		BUTTONEXIT
		return;
	}



	void RobotIO::moveForward(float millimeters, bool keepGoing)
	{
		updateIRDistances();
		float leftGap = irDistances[LEFT];
		float rightGap = irDistances[RIGHT];
		float lastLeftGap = irDistances[LEFT];
		float lastRightGap = irDistances[RIGHT];
		float leftDeltaGap = 0;
		float rightDeltaGap = 0;
		
		millimeters += leftoverDistance;
		leftoverDistance = 0;

		leftMotor.setMaxSpeed(0.21f);
		rightMotor.setMaxSpeed(0.2f);

		PIDController centerPID = PIDController(1.5f, 0.0f, 0.0f, 25.0f);
		PIDController anglePID = PIDController(0.24f, 0.0f, 0.4f, 1000.0f);
		Timer timer = Timer();

		centerPID.start(rightGap - leftGap);
		anglePID.start(0);
		timer.start();
		leftMotor.resetCounts();
		rightMotor.resetCounts();

		bool leftWall = false;
		bool rightWall = false;

		//leftMotor.setMovement(1);
		//rightMotor.setMovement(1);

		Recorder<float> rec = Recorder<float>(2048, 2);

		while (!isWallinDirection(N) && millimeters > 0)
		{
			float deltaTime = timer.getDeltaTime();

			updateIRDistances();

			bool wallChanged = false;

			if (leftWall && irDistances[LEFT] > 100.0f)
			{
				leftWall = false;
				wallChanged = true;
			}
			else if (!leftWall && irDistances[LEFT] < 80.0f)
			{
				leftWall = true;
				wallChanged = true;
			}

			if (rightWall && irDistances[RIGHT] > 100.0f)
			{
				rightWall = false;
				wallChanged = true;
			}
			else if (!rightWall && irDistances[RIGHT] < 80.0f)
			{
				rightWall = true;
				wallChanged = true;
			}

			Serial.print(leftWall ? 1 : 0);
			Serial.print(", ");
			Serial.println(rightWall ? 1 : 0);

			if (leftWall)
			{
				lastLeftGap = 0.9f * lastLeftGap + 0.1f * leftGap;
				if (abs(irDistances[LEFT] - leftGap) > 4.0f)
				{
					leftGap = 0.9f * leftGap + 0.1f * irDistances[LEFT];
				}
				leftDeltaGap = 0.9 * leftDeltaGap + 0.1 * (leftGap - lastLeftGap) / deltaTime;
			}
			
			if (rightWall)
			{
				lastRightGap = 0.9f * lastRightGap + 0.1f * rightGap;
				if (abs(irDistances[RIGHT] - rightGap) > 4.0f)
				{
					rightGap = 0.9f * rightGap + 0.1f * irDistances[RIGHT];
				}
				rightDeltaGap = 0.9 * rightDeltaGap + 0.1 * (rightGap - lastRightGap) / deltaTime;
			}

			if (wallChanged)
			{
				lastLeftGap = leftGap;
				leftDeltaGap = 0;
				lastRightGap = rightGap;
				rightDeltaGap = 0;
				centerPID.start(rightGap - leftGap);
				anglePID.start(0);
				wallChanged = false;
			}

			int leftCounts = leftMotor.resetCounts();
			int rightCounts = rightMotor.resetCounts();
			float leftDist = leftCounts / COUNTS_PER_MM;
			float rightDist = rightCounts / COUNTS_PER_MM;
			float avgDist = (leftDist + rightDist) / 2.0f;
			millimeters -= avgDist;

			float centerCorrection = 0;
			float angleCorrection = 0;

			if (leftWall && rightWall)
			{
				centerCorrection = centerPID.getCorrection(rightGap - leftGap);
				angleCorrection = anglePID.getCorrection(rightDeltaGap - leftDeltaGap);
			}
			else if (leftWall)
			{
				centerCorrection = centerPID.getCorrection(WALL_DISTANCE - 2 * leftGap);
				angleCorrection = anglePID.getCorrection(-2*leftDeltaGap);
			}
			else if (rightWall)
			{
				centerCorrection = centerPID.getCorrection(2 * rightGap - WALL_DISTANCE);
				angleCorrection = anglePID.getCorrection(2*rightDeltaGap);
			}

			centerCorrection /= 2.0f;
			angleCorrection /= 2.0f;

			angleCorrection *= 1 - abs(centerCorrection*centerCorrection);

			float leftSpeed = 1;
			float rightSpeed = 1;

			if (centerCorrection < 0) leftSpeed *= 1 + centerCorrection;
			else rightSpeed *= 1 - centerCorrection;

			if (angleCorrection < 0) leftSpeed *= 1 + angleCorrection;
			else rightSpeed *= 1 - angleCorrection;

			leftMotor.setMovement(leftSpeed);
			rightMotor.setMovement(rightSpeed);

			//Serial.println(angleCorrection, 4);

			/*Serial.print(leftGap, 4);
			Serial.print(", ");
			Serial.print(lastLeftGap, 4);
			Serial.print(", ");
			Serial.println(leftDeltaGap, 4);*/
		}

		updateIRDistances();
		leftoverDistance += millimeters;

		if (!keepGoing || isWallinDirection(N))
		{
			leftMotor.brake();
			rightMotor.brake();
			Timer::sleep(0.2);
		}

		//rec.print();
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
		BUTTONFLAG

		rotate(90);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(-90);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		BUTTONFLAG

		rotate(45);

#ifdef __MK20DX256__ // Teensy Compile
		delay(1000);
#endif
		rotate(-45);

		BUTTONEXIT
			return;
	}



	void RobotIO::rotate(float degrees)
	{
		leftMotor.setMaxSpeed(0.16f);
		rightMotor.setMaxSpeed(0.16f);

		PIDController speedPID = PIDController(30.f, 2.0f, 1.0f , 100.0f);

		PIDController anglePID = PIDController(150.0f, 0.0f , 0.0f, 1000.0f);


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
			BUTTONFLAG

			updateIRDistances();

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
			speedCorrection = 0;

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

		BUTTONEXIT

		leftMotor.brake();
		rightMotor.brake();

		Timer::sleep(0.2f);

		updateIRDistances();
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


	void RobotIO::calibrateMotors()
	{
		rightMotor.calibrate();
		leftMotor.calibrate();
	}


	void RobotIO::stopMotors()
	{
		leftMotor.brake();
		rightMotor.brake();
	}
}

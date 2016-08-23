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
			return IRSensors[LEFT]->getDistance() < 110;

        case E:
			return IRSensors[RIGHT]->getDistance() < 110;

        case N:
		{
			return irDistances[FRONT_LEFT] < 55 && irDistances[FRONT_RIGHT] < 55;
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



	void RobotIO::updateIRDistances()
	{
		// Gather N samples from each sensor, where N is IR_SAMPLE_SIZE
		float samples[N_IR_SENSORS][IR_SAMPLE_SIZE];
		float averages[N_IR_SENSORS];

		for (int a = 0; a < IR_SAMPLE_SIZE; a++)
		{
			Timer::sleep(0.02);
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

		// For each IR sensor...
		for (int n = 0; n < N_IR_SENSORS; n++)
		{
			// ...selection sort each sample by its distance to the average.
			for (int b = 0; b < IR_SAMPLE_SIZE - 1; b++)
			{
				// Find the index of the closest sample:
				int closestA;
				float nearestDistToAvg = std::numeric_limits<float>::infinity();
				for (int a = b; a < IR_SAMPLE_SIZE; a++)
				{
					float dist = abs(averages[n] - samples[n][a]);
					if (dist < nearestDistToAvg)
					{
						nearestDistToAvg = dist;
						closestA = a;
					}
				}

				// Swap the closest sample with the sample at b
				float temp = samples[n][b];
				samples[n][b] = samples[n][closestA];
				samples[n][closestA] = temp;
			}
		}

		for (int n = 0; n < N_IR_SENSORS; n++)
		{
			float avg = 0;
			for (int a = 0; a < IR_AVG_SIZE; a++)
			{
				avg += samples[n][a];
			}
			avg /= IR_AVG_SIZE;

			irDistances[n] = avg;

			/*
			if (abs(irDistances[n] - avg) > 1.0f)
			{
				irDistances[n] = avg;
			}*/
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
		/*
		continuousMoveForward(100.0f * 180.0f, true);
		rotate(180.0f);
		continuousMoveForward(100.0f * 180.0f, true);
		leftMotor.brake();
		rightMotor.brake();
		*/
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



	void RobotIO::continuousMoveForward(float millimeters, bool keepGoing)
	{
		updateIRDistances();
		float leftGap = irDistances[LEFT];
		float rightGap = irDistances[RIGHT];
		float lastLeftGap = irDistances[LEFT];
		float lastRightGap = irDistances[RIGHT];
		float leftDeltaGap = 0;
		float rightDeltaGap = 0;
		
		millimeters += leftoverDistance;

		leftMotor.setMaxSpeed(0.21f);
		rightMotor.setMaxSpeed(0.2f);

		PIDController centerPID = PIDController(1.5f, 0.0f, 0.0f, 25.0f);
		PIDController anglePID = PIDController(0.24f, 0.0f, 0.4f, 1000.0f);
		Timer timer = Timer();

		centerPID.start(0);
		anglePID.start(0);
		timer.start();
		leftMotor.resetCounts();
		rightMotor.resetCounts();

		//leftMotor.setMovement(1);
		//rightMotor.setMovement(1);

		Recorder<float> rec = Recorder<float>(2048, 2);

		while (!isWallinDirection(N))
		{
			float deltaTime = timer.getDeltaTime();

			updateIRDistances();

			lastLeftGap = 0.9f * lastLeftGap + 0.1f * leftGap;
			lastRightGap = 0.9f * lastRightGap + 0.1f * rightGap;
			if (abs(irDistances[LEFT] - leftGap) > 4.0f)
			{
				leftGap = 0.9f * leftGap + 0.1f * irDistances[LEFT];
			}
			if (abs(irDistances[RIGHT] - rightGap) > 4.0f)
			{
				rightGap = 0.9f * rightGap + 0.1f * irDistances[RIGHT];
			}
			leftDeltaGap = 0.9 * leftDeltaGap + 0.1 * (leftGap - lastLeftGap) / deltaTime;
			rightDeltaGap = 0.9 * rightDeltaGap + 0.1 * (rightGap - lastRightGap) / deltaTime;

			int leftCounts = leftMotor.resetCounts();
			int rightCounts = rightMotor.resetCounts();
			float leftDist = leftCounts / COUNTS_PER_MM;
			float rightDist = rightCounts / COUNTS_PER_MM;
			float avgDist = (leftDist + rightDist) / 2.0f;
			millimeters -= avgDist;

			float centerCorrection = centerPID.getCorrection(rightGap - leftGap);
			centerCorrection /= 2.0f;
			float angleCorrection = anglePID.getCorrection(rightDeltaGap - leftDeltaGap);
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

		leftMotor.brake();
		rightMotor.brake();

		leftoverDistance += millimeters;

		//rec.print();
	}


	
	void RobotIO::moveForward(float millimeters)
	{
		leftMotor.setMaxSpeed(0.11f);
		rightMotor.setMaxSpeed(0.1f);

		float lmms = millimeters; //Left millimeters
		float rmms = millimeters; //Right millimeters
		float lspd = 0; //Left motor speed (mm per second)
		float rspd = 0; //Right motor speed (mm per second)
		PIDController ldPID = PIDController(25.0f, 200.0f, 15.0f, 200); // Left distance PID
		PIDController rdPID = PIDController(25.0f, 200.0f, 15.0f, 200); // Right distance PID
		PIDController spPID = PIDController(2.0f, 0.0f, 0.0f, 1000); // Left-right relative speed PID

		Recorder<float> recorder = Recorder<float>(2048, 4);
		Timer timer = Timer();

		leftMotor.resetCounts();
		rightMotor.resetCounts();
		ldPID.start(lmms);
		rdPID.start(rmms);
		spPID.start(0);
		timer.start();

		while (lmms > DISTANCE_TOLERANCE
			|| lmms < -DISTANCE_TOLERANCE
			|| rmms > DISTANCE_TOLERANCE
			|| rmms < -DISTANCE_TOLERANCE
			|| lspd > SPEED_TOLERANCE
			|| lspd < -SPEED_TOLERANCE
			|| rspd > SPEED_TOLERANCE
			|| rspd < -SPEED_TOLERANCE
			)
		{
			BUTTONFLAG;
			float dTime = timer.getDeltaTime();

			float lCorr = ldPID.getCorrection(lmms); //Left correction
			float rCorr = rdPID.getCorrection(rmms);

			int lCounts = leftMotor.resetCounts();
			int rCounts = rightMotor.resetCounts();
			float lDist = lCounts / COUNTS_PER_MM;
			float rDist = rCounts / COUNTS_PER_MM;
			lspd = lDist / dTime;
			rspd = rDist / dTime;

			lmms -= lDist;
			rmms -= rDist;

			float sCorr = spPID.getCorrection(rspd - lspd);

			if (sCorr < 0)
			{
				lCorr *= 1 + sCorr;
			}
			else
			{
				rCorr *= 1 - sCorr;
			}

			if (lCorr < 0.004f && lCorr > -0.004)
			{
				if (lCorr > 0) lCorr = 0.004;
				if (lCorr < 0) lCorr = -0.004;
			}
			if (rCorr < 0.004f && rCorr > -0.004)
			{
				if (rCorr > 0) rCorr = 0.004;
				if (rCorr < 0) rCorr = -0.004;
			}

			leftMotor.setMovement(lCorr);
			rightMotor.setMovement(rCorr);

			if (!recorder.addValue(ldPID.lastP_Correction, 0)
				|| !recorder.addValue(ldPID.lastI_Correction, 1)
				|| !recorder.addValue(ldPID.lastD_Correction, 2)
				|| !recorder.addValue(lCorr, 3)
				)
			{
				
			}

			Timer::sleep(1.0f / 50.0f);
		}

		BUTTONEXIT;

		leftMotor.brake();
		rightMotor.brake();

		recorder.print();
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

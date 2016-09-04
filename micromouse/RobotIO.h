#pragma once

#include "Motor.h"
#include "IRSensor.h"
#include "PIDController.h"
#include "Vector.h"
#include "Path.h"
#include "DataQueue.h"


namespace Micromouse
{
	const float MM_BETWEEN_WHEELS = 66.5f;

	//Number of encoder counts per millimeter traveled.
	//360 / (33 * PI)
	const float COUNTS_PER_MM = 3.472472f;

	//How close the robot needs to be to the target distance (in mm) when moving forward.
    const float DISTANCE_TOLERANCE = 1.0f;

	//How slow each motor needs to be turning (in mm per second) before the robot stops.
	const float SPEED_TOLERANCE = 1.0f;

	//How close the robot needs to be to the target angle (in degrees) when rotating.
	const float ANGLE_TOLERANCE = 1.8f;

	//The expected distance between a left/right sensor and the wall (in mm).
	const float WALL_DISTANCE = 55.0f;
	const float FRONT_RIGHT_WALL_DISTANCE = 52.0f;
	const float FRONT_LEFT_WALL_DISTANCE = 58.0f;
	const float AVG_FRONT_WALL_DISTANCE = 65.0f;

	const int N_IR_SENSORS = 4;

	const float MIN_WALL_DISTANCES[N_IR_SENSORS] = {
		90.0f,
		90.0f,
		145.0f,
		145.0f,
	};

	const float MAX_WALL_DISTANCES[N_IR_SENSORS] = {
		110.0f,
		110.0f,
		147.0f,
		147.0f
	};

	const int IR_SAMPLE_SIZE = 4;
	const int IR_SAMPLE_AVG_SIZE = 2;
	const int IR_AVG_SIZE = 3;
	const float IR_SAMPLE_SLEEP_MILLIS = 2;


	const int IR_FRONT_LEFT_PIN = 14;
	const int IR_FRONT_RIGHT_PIN = 15;
	const int IR_LEFT_PIN = 22;
	const int IR_RIGHT_PIN = 23;

	const int MAGNETOMETER_NINE_DOF_SDA_PIN = 18;
	const int MAGNETOMETER_NINE_DOF_SCL_PIN = 19;

	const int MOTOR_RIGHT_FWD_PIN = 12;
	const int MOTOR_RIGHT_BWD_PIN = 11;
	const int MOTOR_RIGHT_PWM_PIN = 9;
	const int ENCODER_RIGHT_FWD_PIN = 8;
	const int ENCODER_RIGHT_BWD_PIN = 5;

	const int MOTOR_LEFT_FWD_PIN = 17;
	const int MOTOR_LEFT_BWD_PIN = 16;
	const int MOTOR_LEFT_PWM_PIN = 10;
	const int ENCODER_LEFT_FWD_PIN = 20;
	const int ENCODER_LEFT_BWD_PIN = 21;

	const int BUTTON_PIN = 6;
	const int SWITCH_A_PIN = 0;
	const int SWITCH_B_PIN = 2;
	const int SWITCH_C_PIN = 4;

	const int LED_PIN = 13;

	//Memory.h
	extern const int IR_FRONT_LEFT_MEMORY;
	extern const int IR_FRONT_RIGHT_MEMORY;
	extern const int IR_LEFT_MEMORY;
	extern const int IR_RIGHT_MEMORY;


	//A class that contains functions and constants used to communicate with the IO pins of the Teensey 3.2 Microcontroller.
	// ## NOT YET IMPLEMENTED ##
	class RobotIO
	{
	public:
		RobotIO();
		~RobotIO();

		void testMotors(); //temp
		void testIR();
		void testRotate();
		void printIRDistances();
		void updateIRDistances();

		//Moves the bot forward by the given number of millimeters.
		void moveForward(float millimeters, bool keepGoing);

		//Rotates the bot in place by the given number of degrees.
		//Positive values turn the bot to the right. Negative values turn it to the left.
		void rotate(float degrees);

		bool isClearForward(); // Returns false if the range-finder sensors detect a wall in front of the bot. Otherwise, returns true.
		bool isClearRight(); // Returns false if the range-finder sensors detect a wall to the right of the bot. Otherwise, returns true.
		bool isClearLeft(); // Returns false if the range-finder sensors detect a wall to the left of the bot. Otherwise, returns true.

		void followPath(Path * path);

		void calibrateIRSensors();

		void calibrateMotors();

		void stopMotors();

	private:

		enum IRDirection { LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT };

		float irDistances[N_IR_SENSORS];
		DataQueue irDataQueues[N_IR_SENSORS] = {
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE)
		};

		float irDeltas[N_IR_SENSORS];
		DataQueue oldIrDataQueues[N_IR_SENSORS] = {
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE),
			DataQueue(IR_AVG_SIZE)
		};

		bool isWall[N_IR_SENSORS];
		bool irInit = false;

        bool isWallinDirection( direction dir );
		float estimateHeadingError();

		void initIRSensors();

		float leftoverDistance = 0;

		IRSensor* IRSensors[4];

		Motor leftMotor = Motor
		(
			MOTOR_LEFT_FWD_PIN,
			MOTOR_LEFT_BWD_PIN,
			MOTOR_LEFT_PWM_PIN,
			ENCODER_LEFT_FWD_PIN,
			ENCODER_LEFT_BWD_PIN
		);

		Motor rightMotor = Motor
		(
			MOTOR_RIGHT_FWD_PIN,
			MOTOR_RIGHT_BWD_PIN,
			MOTOR_RIGHT_PWM_PIN,
			ENCODER_RIGHT_FWD_PIN,
			ENCODER_RIGHT_BWD_PIN
		);
	};
}
#pragma once

#include "Motor.h"
#include "IRSensor.h"
#include "Vector.h"

namespace Micromouse
{
	const int IR_FRONT_LEFT_PIN = 14;
	const int IR_FRONT_RIGHT_PIN = 15;
	const int IR_LEFT_PIN = 22;
	const int IR_RIGHT_PIN = 23;

	const int MOTOR_RIGHT_FWD_PIN = 11;
	const int MOTOR_RIGHT_BWD_PIN = 12;
	const int MOTOR_RIGHT_PWM_PIN = 9;
	const int ENCODER_RIGHT_FWD_PIN = 8;
	const int ENCODER_RIGHT_BWD_PIN = 7;

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


	//A class that contains functions and constants used to communicate with the IO pins of the Teensey 3.2 Microcontroller.
	// ## NOT YET IMPLEMENTED ##
	class RobotIO
	{
	public:
		RobotIO();
		~RobotIO();

		void moveForward(); // ## NOT YET IMPLEMENTED ## Moves the bot forward by half a cell ( 9 cm ).
		void rotateRight(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the right.
		void rotateLeft(); // ## NOT YET IMPLEMENTED ## Rotates the bot in place 45 degrees to the left.

		bool isClearForward(); // Returns false if the range-finder sensors detect a wall in front of the bot. Otherwise, returns true.
		bool isClearRight(); // Returns false if the range-finder sensors detect a wall to the right of the bot. Otherwise, returns true.
		bool isClearLeft(); // Returns false if the range-finder sensors detect a wall to the left of the bot. Otherwise, returns true.

	private:
#ifdef __MK20DX256__
		Motor rightMotor = Motor
		(
			MOTOR_RIGHT_FWD_PIN,
			MOTOR_RIGHT_BWD_PIN,
			MOTOR_RIGHT_PWM_PIN,
			ENCODER_RIGHT_FWD_PIN,
			ENCODER_RIGHT_BWD_PIN
		);

		Motor leftMotor = Motor
		(
			MOTOR_LEFT_FWD_PIN,
			MOTOR_LEFT_BWD_PIN,
			MOTOR_LEFT_PWM_PIN,
			ENCODER_LEFT_FWD_PIN,
			ENCODER_LEFT_BWD_PIN
		);
#endif
        bool isWallinDirection( direction dir );
	
		enum IRDirection { LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT };

		void initSensors();

		IRSenor* IRSensors[4];
	};
}
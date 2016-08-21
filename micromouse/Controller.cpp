#include "Controller.h"
#include "Logger.h"
#include <vector>
#include "Timer.h"
#include "ButtonFlag.h"

#ifdef __MK20DX256__ // Teensy Compile
	#include "WProgram.h"
#else // pc compile
	#include <iostream>
#endif



//comment / uncomment to turn off / on the debug function.
#define MICROMOUSE_DEBUG_MODE



extern volatile bool buttonFlag;

// defined in RobotIO.h
extern int SWITCH_A_PIN; 
extern int SWITCH_B_PIN;
extern int SWITCH_C_PIN;
extern int LED_PIN;
extern int BUTTON_PIN;



namespace Micromouse
{
	void Controller::debug()
	{
		// DEBUG CODE GOES IN HERE!

		//mouse.mapMaze();
		//mouse.runMaze();
		//mouse.testIR();
		mouse.testMotors();
		//mouse.robotIO.printIRDistances();
		//mouse.testRotate();

		// DEBUG CODE GOES IN HERE!
	}



	Controller::Controller()
	{
		log(INFO) << "Starting Program";

		initPins();
		blinkLED(1); //signifies loading complete
		runMainLoop();

		log(INFO) << "End Program\n\n\n";
	}



	Controller::~Controller()
	{
	}


	void Controller::runMainLoop()
	{
		while (true)
		{	
			waitForButton();

			updateState();

			while (!buttonFlag && state != NONE)
			{
				runState();
			}
		}
	}



	void Controller::updateState()
	{
		int intState;

#ifdef __MK20DX256__ // Teensy Compile
		intState = digitalRead(SWITCH_C_PIN);
		intState <<= 1; intState += digitalRead(SWITCH_B_PIN);
		intState <<= 1; intState += digitalRead(SWITCH_A_PIN);
#else // pc compile
		log(INFO) <<
			"Choose State\n"
			"0: do nothing\n"
			"1: map maze\n"
			"2: run maze\n"
			"3: cycle speed\n"
			"4: debug\n"
			"5: calibrate sensors\n"
			"6: calibrate motor\n"
			"7: reset Map\n";

		std::cin >> intState;
#endif

		state = static_cast<states>(intState);
		log(INFO) << state;
	}



	void Controller::runState()
	{
		switch (state)
		{
		case NONE:
			log(DEBUG2) << "Enter the NONE state";
		break;


		case MAP_MAZE:
			log(DEBUG2) << "Enter the MAP_MAZE state";

			blinkLEDCountdown(3);

			mouse.resetToOrigin();
			mouse.mapMaze();

			if (buttonFlag)
			{
				return;
			}
			else
			{
				doneMap = true;
				state = RUN_MAZE;
				return;
			}

		break;


		case RUN_MAZE:
			log(DEBUG2) << "Enter the RUN_MAZE state";

			if (doneMap)
			{
				blinkLEDCountdown(3);

				mouse.resetToOrigin();
				mouse.runMaze();

				if (buttonFlag)
				{
					return;
				}
				else
				{
					mouse.incrementSpeed();

					if (mouse.getSpeed() == 1 )//full cycle
					{
						state = NONE;
					}

					return;
				}
			}
			else
			{
				log(WARN) << "Must map before Run";
				state = NONE;
			}

		break;


		case SELECT_SPEED:
			log(DEBUG2) << "Enter the SELECT_SPEED state";

			mouse.incrementSpeed();
			blinkLED(mouse.getSpeed());
			state = NONE;
		break;


		case DEBUG_MODE:
			log(DEBUG2) << "Enter the DEBUG_MODE state";
			blinkLEDCountdown(3);
			debug();
			state = NONE;
		break;


		case CAL_SENSORS:
			log(DEBUG2) << "Enter the CAL_SENSORS state";

			blinkLED(CAL_SENSORS);
			state = NONE;
			// I dont want to mess up the calibration during testing
			//TODO test the calbration through the controller states
			//mouse.CalibrateIRSensors();
			//state = NONE;
		break;


		case CAL_MOTOR:
			log(DEBUG2) << "Enter the CAL_MOTOR state";

			blinkLED(CAL_MOTOR);
			state = NONE;
			mouse.robotIO.calibrateMotors();
		break;


		case RESET_MAZE:
			log(DEBUG2) << "Enter the RESET_MAZE state";

			doneMap = false;
			log(INFO) << "Maze Reset";
			mouse.resetMaze();
			state = NONE;

			blinkLED(5);
		break;
		}
	}
	


	int Controller::blinkLED(int reps, int timeOff, int timeOn)
	{
#ifdef __MK20DX256__ // Teensy Compile
		digitalWrite(LED_PIN, LOW);
		delay(timeOff);
		digitalWrite(LED_PIN, HIGH);

		for (; reps >= 2; reps--)
		{
			BUTTONFLAG

			delay(timeOn);
			digitalWrite(LED_PIN, LOW);
			delay(timeOff);
			digitalWrite(LED_PIN, HIGH);
		}
#endif
		BUTTONEXIT
		return(timeOff * reps + timeOn * (reps - 1));
	}



	void Controller::blinkLEDCountdown(int sec)
	{
		log(INFO) << "countdown";

		for (; sec > 5; sec--) //long single blinks for more than 5 seconds
		{
			BUTTONFLAG

			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy Compile
			delay(1000 - blinkLED( 1 , 200 ));
#endif
		}

		for (; sec > 0; sec--)//quick blinks for the number of seconds left
		{
			BUTTONFLAG

			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy Compile
			delay(1000 - blinkLED(sec, 80, 50));
#endif
		}

		BUTTONEXIT
		return;
	}



	void Controller::waitForButton()
	{
		buttonFlag = false;
#ifdef __MK20DX256__ // Teensy Compile
		while (!buttonFlag)
		{
			delay(10);
		}
#else // pc
		system("pause");
#endif
		buttonFlag = false;
	}


	void irsButtonFlag()
	{
#ifdef __MK20DX256__ // Teensy Compile
		cli();

		if (!buttonFlag)
		{
			buttonFlag = true;
		}

		sei();
#endif
	}


	void Controller::initPins()
	{
#ifdef __MK20DX256__ // Teensy Compile
		pinMode(BUTTON_PIN, INPUT_PULLUP);
		attachInterrupt(BUTTON_PIN, irsButtonFlag, RISING);
		pinMode(SWITCH_A_PIN, INPUT_PULLUP);
		pinMode(SWITCH_B_PIN, INPUT_PULLUP);
		pinMode(SWITCH_C_PIN, INPUT_PULLUP);
#endif
	}
}



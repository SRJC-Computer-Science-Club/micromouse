#include "Controller.h"
#include "Logger.h"
#include <vector> //must come first for some reason

#ifdef __MK20DX256__ // Teensy compile
#include "WProgram.h"
#else // pc compile
#include <iostream>
#endif

int buttonFlag;

extern int SWITCH_A_PIN; // defined in RobotIO.h
extern int SWITCH_B_PIN;
extern int SWITCH_C_PIN;

extern int LED_PIN;
extern int BUTTON_PIN;

//comment / uncomment to turn off / on the debug function.
#define MICROMOUSE_DEBUG_MODE

namespace Micromouse
{
	void Controller::debug()
	{
		// DEBUG CODE GOES IN HERE!

		mouse.testMotors();

		// DEBUG CODE GOES IN HERE!
	}

	Controller::Controller()
	{
		log(INFO) << "Starting Program"; //log to console only

		#ifdef MICROMOUSE_DEBUG_MODE
			debug();
		#else
			runMainLoop();
		#endif

		logC( DEBUG1 ) << "End Program"; //log to console only
	}


	Controller::~Controller()
	{
	}


	void Controller::runMainLoop()
	{
		while (true)
		{
			updateState();

			while (!buttonFlag && state != NONE)
			{
				runState();
			}
			waitForButton();
			buttonFlag = false;
		}
	}


	void Controller::updateState()
	{
		int intState;
#ifdef __MK20DX256__ // Teensy compile

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
			"4: nothing\n"
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
			break;


		case MAP_MAZE:
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
			mouse.incrementSpeed();
			blinkLED(mouse.getSpeed());
			state = NONE;

			break;


		case NONE_4:

			break;


		case CAL_SENSORS:
			mouse.CalibrateIRSensors();
			state = NONE;
			break;


		case CAL_MOTOR:
			//TODO
			break;


		case RESET_MAZE:
			doneMap = false;
			log(INFO) << "Maze Reset";
			//TODO
			state = NONE;
			break;
		}

	}


	int Controller::blinkLED(int reps, int timeOn, int timeOff)
	{
#ifdef __MK20DX256__ // Teensy compile
		digitalWrite(LED_PIN, HIGH);
		delay(timeOn);
		digitalWrite(LED_PIN, LOW);

		for (; reps >= 2; reps--)
		{
			delay(timeOff);

			digitalWrite(LED_PIN, HIGH);
			delay(timeOn);
			digitalWrite(LED_PIN, LOW);
		}
#endif
		return(timeOn * reps + timeOff * (reps - 1));
	}

	void Controller::blinkLEDCountdown(int sec)
	{
		log(INFO) << "countdown";

		for (; sec > 5; sec--) //long single blinks for more than 5 seconds
		{
			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy compile
			delay(1000 - blinkLED( 1 , 200 ));
#endif
		}

		for (; sec > 0; sec--)//quick blinks for the number of seconds left
		{
			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy compile
			delay(1000 - blinkLED(sec, 80, 50));
#endif
		}
	}

	void Controller::waitForButton()
	{
#ifdef __MK20DX256__ // Teensy compile
		while (!digitalRead(BUTTON_PIN))
		{
			delay(10);
		}
#else // pc
		system("pause");
		buttonFlag = true;
#endif
	}


}
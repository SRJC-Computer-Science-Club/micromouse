#include "Controller.h"
#include "Logger.h"
#include <vector>

#ifdef __MK20DX256__ // Teensy compile
#include "WProgram.h"
#else // pc compile
#include <iostream>
#endif

int buttonFlag;

const int SWITCH_A_PIN = 0; // defined in RobotIO.h
const int SWITCH_B_PIN =1;
const int SWITCH_C_PIN =2;

const int LED_PIN = 2;

namespace Micromouse
{

	Controller::Controller()
	{
		log(INFO) << "Starting Program"; //log to console only
		
		while (true)
		{
			updateState();
			
			while (!buttonFlag && state != NONE )
			{
				runState();
			}

			waitForButton();
			buttonFlag = false;
		}

		logC( DEBUG1 ) << "End Program"; //log to console only
	}


	Controller::~Controller()
	{
	}


	void Controller::updateState()
	{
		int intState;
#ifdef __MK20DX256__ // Teensy compile

		intState = digitalRead(SWITCH_C_PIN);
		intState << 1; intState += digitalRead(SWITCH_B_PIN);
		intState << 1; intState += digitalRead(SWITCH_A_PIN);

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
			mouse.CalibrateSensors();
			break;


		case CAL_MOTOR:
			//TODO
			break;


		case RESET_MAZE:
			doneMap = false;
			//TODO
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
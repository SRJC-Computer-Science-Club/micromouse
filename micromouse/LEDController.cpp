#include <LEDController.h>
#ifdef __MK20DX256__ // Teensy Compile
	#include "WProgram.h"
#else // pc compile
	#include <iostream>
#endif



//comment / uncomment to turn off / on the debug function.
#define MICROMOUSE_DEBUG_MODE



int buttonFlag;



namespace Micromouse
{
    
    LEDController::LEDController()
    {
    }
    LEDController::~LEDController()
    {
    }


	int LEDController::blinkLED(int reps, int timeOn, int timeOff)
	{
#ifdef __MK20DX256__ // Teensy Compile
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



	void LEDController::blinkLEDCountdown(int sec)
	{
		log(INFO) << "countdown";

		for (; sec > 5; sec--) //long single blinks for more than 5 seconds
		{
			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy Compile
			delay(1000 - blinkLED( 1 , 200 ));
#endif
		}

		for (; sec > 0; sec--)//quick blinks for the number of seconds left
		{
			log(INFO) << sec;
#ifdef __MK20DX256__ // Teensy Compile
			delay(1000 - blinkLED(sec, 80, 50));
#endif
		}
	}
}
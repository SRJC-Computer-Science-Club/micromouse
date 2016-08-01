#ifndef TEENSYFUNCTIONS_H
#define TEENSYFUNCTIONS_H

#include "ButtonFlag.h"
//Teensy PC safe versions
//Controller.cpp

extern volatile bool buttonFlag;

#ifdef __MK20DX256__ // Teensy Compile
#else //on windows
void delay(unsigned long milliseconds){};
#endif

#ifdef __MK20DX256__ // Teensy Compile
#else //on windows
void digitalWrite(int pin, bool high){};
#endif

//The above definitions already complete 
//Line 237
//Line 263
//Line 273
//Line 287

//Line 301
#ifdef __MK20DX256__ // Teensy Compile
#else
		void cli(){};
        
		if (!buttonFlag)
		{
			buttonFlag = true;
		} 

		void sei(){};
#endif

//Line 316
#ifdef __MK20DX256__ // Teensy Compile
#else 
		void pinMode(int pin, bool mode){};
		void attachInterrupt(int pin, bool mode){};
#endif

//IRSensor.cpp
//Line 6
#ifdef __MK20DX256__ // Teensy Compile
#else 
    #include <iostream>
#endif

//Line 48 already done
//Line 151 as well
//Line 201 -- pinMode (here on line 41) may fix it

//Logger.h
//Line 3 already done
//Line 57 as well
//Line 113 as well
//Line 123 as well
//Line 138 -- 
//Line 151 done
//Line 177 done
#endif
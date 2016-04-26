//
//  teensy.hpp
//  yyekalo
//
//  Created by Yekalo Berhane on 4/22/16.
//  Copyright © 2016 Yikealo Abraha. All rights reserved.
//

#pragma once

#ifdef __MK20DX256__ // Teensy Compile
#include <Arduino.h>
#endif




#define HIGH 1;
#define LOW 2;
#define OUTPUT 1;
#define INPUT 0;
#define INPUT_PULLUP 2;

void digitalWrite2(int port,int state);

void anglogWrite2(int port,int value);

int analogRead2(int port);

int digitalRead2(int port);

void pinMode2(int port,int purpose);

void delay2(int time);

void delayMicroseconds2(int microsecond);

int random2(int value);

//cli
//sei

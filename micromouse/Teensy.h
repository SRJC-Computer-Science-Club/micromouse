//
//  Teensy.hpp
//  yyekalo
//
//  Created by Yikealo on 4/22/16.
//  Copyright © 2016 Yikealo Abraha. All rights reserved.
//

#pragma once

#ifdef __MK20DX256__ // Teensy Compile
#include <Arduino.h>
#else





#define HIGH 1;
#define LOW 2;
#define OUTPUT 1;
#define INPUT 0;
#define INPUT_PULLUP 2;

void digitalWrite(int port,int state);

void analogWrite(int port,int value);

int analogRead(int port);

int digitalRead(int port);

void pinMode(int port,int purpose);

void delay(int time);

void delayMicroseconds(int microsecond);

int random(int value);

//cli
//sei
#endif


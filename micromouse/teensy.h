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
#else // PC compile
#include <iostream>
#include <fstream>
#include <sstream>
#endif




#define HIGH 1;
#define LOW 2;

enum purpose {OUTPUT,INPUT};

void digitalWrite2(int port,int state);

void anglogWrie2(int port,int value);

int analogRead2(int port);

int digitalRead2(int port);

void pinMode2(int,purpose);

void delay2();

void delayMicroseconds2();

int random2(int min=0,int max=100);

//cli
//sei
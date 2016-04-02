#pragma once
#include <math.h>
/*
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
pinMode(7, INPUT);
*/

#ifdef __MK20DX256__ 
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
#endif

class Magnetometer
{
private:
	float mag    = 0;
	float degree = 0;
	float offset = 0;
public:
	float getDegrees();
	Magnetometer();
	~Magnetometer();
};


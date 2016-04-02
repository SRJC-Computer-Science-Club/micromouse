#pragma once
namespace Micromouse
{
#ifdef __MK20DX256__ 

//#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

	Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

	void setupSensor()
	{
		//the magnetometer sensitivity    v
		lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);
	}

	void setup()
	{
#ifndef ESP8266
		while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
		Serial.begin(9600);
		pinMode(7, INPUT);
		Serial.println("LSM raw read demo");

		// Try to initialise and warn if we couldn't detect the chip
		if (!lsm.begin())
		{
			Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
			while (1);
		}
		Serial.println("Found LSM9DS0 9DOF");
		Serial.println("");
		Serial.println("");

	}
#endif

	class Magnetometer
	{
	private:
		float mag = 0;
		float degree = 0;
		float offset = 0;
	public:
		float getDegrees();
		Magnetometer();
		~Magnetometer();
	};

}
#pragma once
#ifdef __MK20DX256__ 

#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

#endif
namespace Micromouse
{
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

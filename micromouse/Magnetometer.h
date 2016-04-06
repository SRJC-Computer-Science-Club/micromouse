#pragma once
#ifdef __MK20DX256__ 
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#endif
namespace Micromouse
{
	class Magnetometer
	{

	public:
		float getDegrees();
		//direction getHeading();
		Magnetometer();
		~Magnetometer();
	private:
		void initSensor();

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
#endif
	};
	
}

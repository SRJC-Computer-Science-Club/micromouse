#pragma once
#ifdef __MK20DX256__
#include <math.h>
#include <Adafruit_LSM9DS0.h>
#endif
namespace Micromouse
{
	class Magnetometer
	{

	public:
		//Gets degrees IE returns '56' degrees from north
		float getDegrees();
		//TODO function to get direction 
		//direction getHeading();
		
		//initialised the sensor to read data when object is created
		Magnetometer();
		~Magnetometer();
	private:
		void initSensor();
		float getDegreesRaw();

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 sensorREAD = Adafruit_LSM9DS0();
#endif
	};
	
}

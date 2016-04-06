#pragma once
#include "Vector.h"
#ifdef __MK20DX256__
#include <math.h>
#include "Adafruit_LSM9DS0.h"
#endif
namespace Micromouse
{
	class Magnetometer
	{

	public:
		//how to define magnetometer object
		//#include "Magnetometer.h"
		//Magnetometer OBJECTNAME = Magnetometer(18,19);
		//OBJECTNAME.getDegrees();

		float getDegrees();
		void initDirection();
		//TODO function to get direction 
		direction getDirection();
		
		//initialised the sensor to read data when object is created
		Magnetometer(const int MAGNETOMETER_NINE_DOF_SDA_PIN, const int MAGNETOMETER_NINE_DOF_SCL_PIN);

		~Magnetometer();
	private:
		float initialDirection = 0.0f;
		void initSensor();
		float getDegreesRaw();

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 sensorREAD = Adafruit_LSM9DS0();
#endif
	};
	
}

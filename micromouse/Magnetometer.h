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
		//Magnetometer test
		//test.getDegrees();
		float getDegrees();
		void setNorth();
		//TODO function to get direction 
		//direction getHeading();
		
		//initialised the sensor to read data when object is created
		Magnetometer(const int MAGNETOMETER_NINE_DOF_SDA_PIN, const int MAGNETOMETER_NINE_DOF_SCL_PIN);

		~Magnetometer();
	private:
		void initSensor();
		float getDegreesRaw();

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 sensorREAD = Adafruit_LSM9DS0();
#endif
	};
	
}

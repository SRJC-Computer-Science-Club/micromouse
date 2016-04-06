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
		float getDegrees();
		//direction getHeading();
		Magnetometer();
		~Magnetometer();
	private:
		void initSensor();
		float getDegreesRaw();

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
#endif
	};
	
}

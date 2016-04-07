#include "Magnetometer.h"
#include "Logger.h"



namespace Micromouse
{
	float Magnetometer::getDegrees()
	{
		return getDegreesRaw() - initialDirection;
	}






	void Magnetometer::initDirection()
	{
		initialDirection = getDegreesRaw();
	}






	
	float Magnetometer::getDegreesRaw()
	{

	#ifdef __MK20DX256__ 

			sensorREAD.read();
			float degrees = atan2(sensorREAD.magData.y, sensorREAD.magData.x);
			degrees *= 57.296f;
			return degrees;

	#endif

			return 0.0f;
	}







	direction Magnetometer::getDirection()
	{
		return (direction)((int)(getDegrees() - 22.5) / 45);
	}






	void Magnetometer::initSensor()
	{
		initDirection();

	#ifdef __MK20DX256__ 
		//Set magnetometer sensitivity
		sensorREAD.setupMag(sensorREAD.LSM9DS0_MAGGAIN_12GAUSS);

		//checks to see if there is data comming from magnetometer
		if (!sensorREAD.begin())
		{  

			log(ERROR) << "Oops ... unable to initialize the LSM9DS0. Check your wiring!";

			while (true);

		}

	#endif

	}






	Magnetometer::Magnetometer()
	{

	#ifdef __MK20DX256__ 

		initSensor();

	#endif

	}






	Magnetometer::~Magnetometer()
	{
	}
}
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
		direction heading = NONE;

		return heading;
	}
	/*direction Magnetometer::getHeading()
	{
		direction heading;
		//Magnetometer::heading = direction((int)(Magnetometer::getDegrees() + 22.5) / 45);
		//return direction(heading);

		return direction();
	}
	*/

		


	





	
	void Magnetometer::initSensor()
	{
		initDirection();
#ifdef __MK20DX256__ 


		//the magnetometer sensitivity
		sensorREAD.setupMag(sensorREAD.LSM9DS0_MAGGAIN_12GAUSS);

		//checks to see if there is data comming from magnetometer
		if (!sensorREAD.begin())
		{  
			log(ERROR) << "Oops ... unable to initialize the LSM9DS0. Check your wiring!";
			while (true);
		}

#endif
	}




	Magnetometer::Magnetometer(const int MAGNETOMETER_NINE_DOF_SDA_PIN, const int MAGNETOMETER_NINE_DOF_SCL_PIN)
	{
#ifdef __MK20DX256__ 

		initSensor();

#endif
	}



	Magnetometer::~Magnetometer()
	{
	}
}
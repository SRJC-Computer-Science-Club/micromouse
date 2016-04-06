#include "Magnetometer.h"
#include "Logger.h"

namespace Micromouse
{
	Magnetometer::Magnetometer()
	{
#ifdef __MK20DX256__ 
		initSensor();
#endif
}


	Magnetometer::~Magnetometer()
	{
	}



	void Magnetometer::initSensor()
	{
#ifdef __MK20DX256__ 
		//the magnetometer sensitivity
		lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);
		// Try to initialise and warn if we couldn't detect the chip

		if (!lsm.begin())
		{
			log(ERROR) << "Oops ... unable to initialize the LSM9DS0. Check your wiring!";
			while (true);
		}
#endif

		zero();
}


	float Magnetometer::getHeading()
	{
		float degree = getDegreesRaw();
		degree += offset;
		degree *= 57.296f;
		return degree;
	}



	float Magnetometer::getDegreesRaw()
	{
#ifdef __MK20DX256__ 
		lsm.read();
		return  atan2(lsm.magData.y, lsm.magData.x);
#else
		return 0.0f;
#endif
	}



	direction Magnetometer::getDirection()
	{
		return direction((int)(getHeading() + 22.5) / 45);
	}



	void Magnetometer::zero()
	{
		float degSum = 0.0;

		for (int i = 0; i < 50; i++)
		{
			degSum += getDegreesRaw();
#ifdef __MK20DX256__ 
			delay(1);
#endif
		}

		offset = -degSum / 50.0;
	}
}
#include "Magnetometer.h"
#include "RobotIO.h"
#include "Logger.h"

namespace Micromouse
{
	float Magnetometer::getDegrees()
	{
#ifdef __MK20DX256__ 
		float mag = atan2(lsm.magData.y, lsm.magData.x);
		// Set starting posistion
		if (BUTTON_PIN == HIGH) {
			offset = -mag;
		}
		lsm.read();
		float degree = (offset + mag) * 57.296;
		return degree;
	}
	
#else
		return degree;
	}
#endif
	/*direction Magnetometer::getHeading()
	{
		return direction();
	}
	*/

		//Magnetometer::heading = direction((int)(Magnetometer::getDegrees() + 22.5) / 45);
		//return direction(heading);


	





	
	void Magnetometer::initSensor()
	{
#ifdef __MK20DX256__ 

		//the magnetometer sensitivity
		lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

		// Try to initialise and warn if we couldn't detect the chip
		if (!lsm.begin())
		{  
			log(ERROR) << "Oops ... unable to initialize the LSM9DS0. Check your wiring!";
			while (1);
		}

#endif
	}





	Magnetometer::Magnetometer()
	{
		initSensor();
	}

	Magnetometer::~Magnetometer()
	{
	}
}
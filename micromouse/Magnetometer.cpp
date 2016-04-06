#include "Magnetometer.h"
#include "Logger.h"

namespace Micromouse
{
	float Magnetometer::getDegrees()
	{
#ifdef __MK20DX256__ 
		float offset = 0;
		lsm.read();
		float magnet = atan2(lsm.magData.y, lsm.magData.x);
		
		//// Set starting posistion
		//if (BUTTON_PIN == HIGH) {
			//offset = -mag;
		//}
		
		float degree = (offset + magnet) * 57.296f;
		return degree;
#endif
		return 0.00f;
	}
	float getDegreesRaw()
	{
		lsm.read();
	}
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
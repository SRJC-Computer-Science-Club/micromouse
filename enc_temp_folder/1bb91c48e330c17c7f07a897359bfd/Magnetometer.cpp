#include "Magnetometer.h"
#include "Logger.h"

namespace Micromouse
{
	float Magnetometer::getDegrees()
	{/*
#ifdef __MK20DX256__ 
		float offset = 0;
		sensorREAD.read();
		float magnet = atan2(sensorREAD.magData.y, sensorREAD.magData.x);
		
		//// Set starting posistion
		//if (BUTTON_PIN == HIGH) {
			//offset = -mag;
		//}
		
		float degree = (offset + magnet) * 57.296f;
		return degree;
#endif
*/
		return 0.00f;
	}
	float Magnetometer::getDegreesRaw()
	{
		//sensorREAD.read();
		return 0.00f;
	}


	/*direction Magnetometer::getHeading()
	{
		//Magnetometer::heading = direction((int)(Magnetometer::getDegrees() + 22.5) / 45);
		//return direction(heading);

		return direction();
	}
	*/

		


	





	
	void Magnetometer::initSensor()
	{
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
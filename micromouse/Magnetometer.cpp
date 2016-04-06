#include "Magnetometer.h"
#include "Logger.h"

namespace Micromouse
{
	float Magnetometer::getDegrees()
	{
		float degree = 0.00f;
#ifdef __MK20DX256__ 
		float offset = 0;
	 	getDegreesRaw();

		float magnet = atan2(sensorREAD.magData.y, sensorREAD.magData.x);
		
		//// Set starting posistion
		//if (BUTTON_PIN == HIGH) {
			//offset = -mag;
		//}
		
		degree = (offset + magnet) * 57.296f;
#else
		return degree;
#endif
	}


	void Magnetometer::setNorth()
	{
	}


	float Magnetometer::getDegreesRaw()
	{
#ifdef __MK20DX256__ 

		//sensorREAD.read();
#endif

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
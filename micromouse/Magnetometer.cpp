#include "Magnetometer.h"
#include "RobotIO.h"
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
		return 0.0f;
	}
#endif
	
	





	void setupSensor()
	{
#ifdef __MK20DX256__ 
		//the magnetometer sensitivity
		lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);
#endif
	}





	

	void setup()
	{
#ifdef __MK20DX256__ 

#ifndef ESP8266
		while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
		//Serial.begin(9600);
		pinMode(7, INPUT);
		Serial.print("LSM raw read demo");

		// Try to initialise and warn if we couldn't detect the chip
		if (!lsm.begin())
		{
			Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
			while (1);
		}
		Serial.println("Found LSM9DS0 9DOF");
		Serial.println("");
		Serial.println("");
#endif
	}





	Magnetometer::Magnetometer()
	{
	}

	Magnetometer::~Magnetometer()
	{
	}
}
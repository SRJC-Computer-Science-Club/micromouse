#include "Magnetometer.h"
namespace Micromouse
{
	float Magnetometer::getDegrees()
	{
#ifdef __MK20DX256__ 
		float mag = atan2(lsm.magData.y, lsm.magData.x);
		if (BUTTON_PIN == HIGH) {// posistion to 0
			offset = -mag;
			//Serial.println("Button Pressed"); //TESTING ONLY
		}
		lsm.read();
		float degree = (offset + mag) * 57.296;
		return degree;
#else
		return 0.0f;
#endif
	}

	Magnetometer::Magnetometer()
	{
	}

	Magnetometer::~Magnetometer()
	{
	}
}
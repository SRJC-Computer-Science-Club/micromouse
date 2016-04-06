#pragma once
#include "Vector.h"

#ifdef __MK20DX256__

#include <math.h>
#include "Adafruit_LSM9DS0.h"

#endif



namespace Micromouse
{

	/*How to use Magnetometer objects
	first include the magnetometer header file

		#include "Magnetometer.h"

	Then to delare an object use the syntax

		Magnetometer  NAME = Magnetometer(18,19);

	or

		Magnetometer  NAME = Magnetometer(MAGNETOMETER_NINE_DOF_SDA_PIN, MAGNETOMETER_NINE_DOF_SCL_PIN);

	To call get direction 

		NAME.getDegrees();

	or to get the direction the robot it facing 

		NAME.getDirection();


	NOTES
		getDegrees is 0.00 -> 360.00 floats
		getDirection returns N (North), S (South).... "direction" data type enum of int's
	*/

	class Magnetometer
	{

	public:

		float getDegrees();
		void initDirection();
		direction getDirection();

		//initialised the sensor to read data when object is created
		Magnetometer(const int MAGNETOMETER_NINE_DOF_SDA_PIN, const int MAGNETOMETER_NINE_DOF_SCL_PIN);
		~Magnetometer();

	private:

		float initialDirection = 0.00f;
		void  initSensor();
		float getDegreesRaw();

	#ifdef __MK20DX256__ 

		Adafruit_LSM9DS0 sensorREAD = Adafruit_LSM9DS0();

	#endif

	};
}

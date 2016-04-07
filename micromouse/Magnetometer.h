#pragma once
#include "Vector.h"

#ifdef __MK20DX256__
#include <math.h>.
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h> 
#endif
namespace Micromouse
{
	class Magnetometer
	{

		// this class represents the magnetometer that is part of the LSM9DS0 9DOF sensor
		// it uses the x and y components of the vector returned by the magnetometer library
		// it calculates the heading of the mouse based on the x and y components
		// zero should be called as part of the calibration process, 
		// the mouse should be facing 'North' relative to the maze when called and should not be touched or moved

	public:
		Magnetometer();
		~Magnetometer();

		float getHeading(); // returns the heading in degrees CW from the north set from zero()
		direction getDirection(); // returns the heading as a direction type N, NW, W etc.

		void zero(); //sets north to the direction mouse is facing
		// takes 50ms 
		// do not call during main run/map routine



	private:
		void initSensor();
		float getHeadingRaw(); // returns the degree without the offset

		float offset;

#ifdef __MK20DX256__ 
		Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(); //todo figure out if the i2c pins need to be set manually and if so how
#endif
	};
	
}

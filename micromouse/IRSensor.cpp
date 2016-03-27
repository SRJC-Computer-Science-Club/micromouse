#include "IRSensor.h"
#include "Logger.h"
#include <assert.h>
#ifdef __MK20DX256__ //this is the Teensy signature
#include "WProgram.h"
#endif

namespace Micromouse {
    
    extern const int BUTTON_PIN;

    extern const int BUTTON_PIN = 10;
    
	//IR SENSORS/////////////////////////

	IRSenor::IRSenor(int pin, int minRange, int maxRange):
		PIN(pin),
		MIN_RANGE(minRange),
		MAX_RANGE(maxRange)
	{
		defaultCalibration();
	}


	IRSenor::~IRSenor()
	{
		delete[] calibrationData;
	}

	bool IRSenor::calibrate( int calibrationStart, int calibrationInterval )
	{
		assert(calibrationStart >= MIN_RANGE);
		assert(calibrationInterval > 0);
		this->calibrationStart = calibrationStart;
		this->calibrationInterval = calibrationInterval;
		this->calibrationSize = MAX_RANGE - calibrationStart / calibrationInterval + 10;

		delete[] calibrationData;
		calibrationData = new int[calibrationSize];

		log(INFO) << "Begin IR calibration";

#ifdef __MK20DX256__ //this is the Teensy signature
		int sampleSize = 20;
		for (int i = 0; i < calibrationSize; i++)
		{
			log(INFO) << "distance: " << (i * calibrationInterval + calibrationStart);

			//TODO use interrupts
			while (!digitalRead(BUTTON_PIN))
			{
				delay(1);
			}
			while (digitalRead(BUTTON_PIN))
			{
				delay(1);
			}


			for (int x = 0; x < sampleSize; x++)
			{
				calibrationData[i] += analogRead(PIN);
				delay(1);
			}

			calibrationData[i] /= sampleSize;
			
			log(INFO) << "analogRead: " << calibrationData[i];
		}
#else
		log(WARN) << "performed pseudo calibration instead";
		defaultCalibration();
#endif

		return false;
	}


	int IRSenor::getDistance()
	{
#ifdef __MK20DX256__ //this is the Teensy signature
		int val = analogRead(PIN);
#else
		// false analog value used while on pc
		int val = 300;
#endif

		for (int i = calibrationSize - 1; i >= 0; i--)
		{
			log(DEBUG3) << "calibrationData[ " << i << " ]= " << calibrationData[i] << " , val = " << val;

			if (val < calibrationData[i])
			{
				float dist = interpolate(calibrationData[i], calibrationData[i + 1],
					i * calibrationInterval + calibrationStart,
					(i + 1) * calibrationInterval + calibrationStart, val);

				log(DEBUG2) << "Measured Distance: " << dist;

				return dist;
			}

			log(DEBUG2) << "Measured Distance*: " << MIN_RANGE;

			return MIN_RANGE;
		}
        // to complile with Xcode win archit.
        return 666;
	}





	float IRSenor::interpolate(int x1, int x2, int y1, int y2, int x)
	{
		return(float(x - x1) / (x2 - x1)*(y2 - y1) + y1);
	}




	void IRSenor::defaultCalibration()
	{
		calibrationData = new int[10];

		if (MIN_RANGE == 40)
		{
			calibrationData[0] = 517; //40mm
			calibrationData[1] = 338; //70mm
			calibrationData[2] = 236; //100mm
			calibrationData[3] = 188; //130mm
			calibrationData[4] = 152; //160mm
			calibrationData[5] = 129; //190mm
			calibrationData[6] = 116; //220mm
			calibrationData[7] = 100; //250mm
			calibrationData[8] = 92; //280mm
			calibrationData[9] = 84; //310mm
		}
		//TODO add default calibration for 2-15cm sensor
	}
}


#include "IRSensor.h"
#include "Logger.h"
#include "RobotIO.h"
#include <assert.h>
#ifdef __MK20DX256__ //this is the Teensy signature
#include "WProgram.h"
#endif

namespace Micromouse {
    
    extern const int BUTTON_PIN;
    
	//IR SENSORS/////////////////////////

	IRSensor::IRSensor(int pin, int minRange, int maxRange):
		DATA_PIN(pin),
		MIN_RANGE(minRange),
		MAX_RANGE(maxRange)
	{
		initPins();
		defaultCalibration();
	}


	IRSensor::~IRSensor()
	{
		delete[] calibrationData;
	}

	bool IRSensor::calibrate( int calibrationStart, int calibrationInterval )
	{
		assert(calibrationStart >= MIN_RANGE);
		assert(calibrationInterval > 0);
		this->calibrationStart = calibrationStart;
		this->calibrationInterval = calibrationInterval;
		calibrationSize = MAX_RANGE - calibrationStart / calibrationInterval + 10;
		assert(calibrationSize <= 17);

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
				calibrationData[i] += analogRead(DATA_PIN);
				delay(1);
			}

			calibrationData[i] /= sampleSize;
			
			log(INFO) << "analogRead: " << calibrationData[i];
		}
#else
		log(WARN) << "performed pseudo calibration instead";
		defaultCalibration();
#endif
		//TODO return true and false on success/failure or change to void function
		return false;
	}



	bool IRSensor::loadCalibration(int address)
	{
		int size = Memory::read(address++);

		if (size > 0 )
		{
			calibrationSize = size;
			calibrationStart = Memory::read(address++);
			calibrationInterval = Memory::read(address++);


			delete[] calibrationData;
			calibrationData = new int[calibrationSize];

			for (int i = 0; i < calibrationSize; i++)
			{
				calibrationData[i] = Memory::read(address++);
			}

			return true;
		}

		return false;
	}

	void IRSensor::saveCalibration(int address)
	{
		Memory::write(address++, calibrationSize);
		Memory::write(address++, calibrationStart);
		Memory::write(address++, calibrationInterval);

		for (int i = 0; i < calibrationSize; i++)
		{
			Memory::write(address++, calibrationData[i]);
		}
	}



	float IRSensor::getDistance()
	{
#ifdef __MK20DX256__ //this is the Teensy signature
		int val = analogRead(DATA_PIN);
#else
		// false analog value used while on pc
		int val = 300;
#endif

		for (int i = calibrationSize - 1; i >= 0; i--)
		{
			log(DEBUG4) << "calibrationData[ " << i << " ]= " << calibrationData[i] << " , val = " << val;

			if (val < calibrationData[i])
			{
				float dist = interpolate(calibrationData[i], calibrationData[i + 1],
					i * calibrationInterval + calibrationStart,
					(i + 1) * calibrationInterval + calibrationStart, val);

				log(DEBUG4) << "Measured Distance: " << dist;

				return dist;
			}

			log(DEBUG4) << "Measured Distance*: " << MIN_RANGE;

			return MIN_RANGE;
		}

		return -1;//code should never reach here
	}





	float IRSensor::interpolate(int x1, int x2, int y1, int y2, int x)
	{
		return(float(x - x1) / (x2 - x1)*(y2 - y1) + y1);
	}




	void IRSensor::initPins()
	{
#ifdef __MK20DX256__ //this is the Teensy signature
		pinMode(DATA_PIN, OUTPUT);
#endif
	}

	void IRSensor::defaultCalibration()
	{
		calibrationSize = 10;
		calibrationInterval = 15;
		calibrationStart = MIN_RANGE;
		calibrationData = new int[10];

		//if (MIN_RANGE == 40)
		//{
		//	calibrationData[0] = 517; //40mm
		//	calibrationData[1] = 338; //70mm
		//	calibrationData[2] = 236; //100mm
		//	calibrationData[3] = 188; //130mm
		//	calibrationData[4] = 152; //160mm
		//	calibrationData[5] = 129; //190mm
		//	calibrationData[6] = 116; //220mm
		//	calibrationData[7] = 100; //250mm
		//	calibrationData[8] = 92; //280mm
		//	calibrationData[9] = 84; //310mm
		//}

		//TODO add default calibration for 2-15cm sensor this is false data
		if (MIN_RANGE == 20)
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
	}
}


#include "IRSensor.h"
#include "Logger.h"
#include "RobotIO.h"
#include <assert.h>

#ifdef __MK20DX256__ // Teensy Compile
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
		calibrationData = new int[1];
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
		calibrationSize = ( MAX_RANGE - calibrationStart ) / calibrationInterval + 1;
		assert(calibrationSize <= 17);

		delete[] calibrationData;
		calibrationData = new int[calibrationSize];

		log(INFO) << "Begin IR calibration";

#ifdef __MK20DX256__ // Teensy Compile
		int sampleSize = 6;

		for (int i = 0; i < calibrationSize; i++)
		{
			log(INFO) << "distance: " << (i * calibrationInterval + calibrationStart);

			//TODO use interrupts
			while (!digitalRead(BUTTON_PIN))
			{
				delay(10);
			}

			while (digitalRead(BUTTON_PIN))
			{
				delay(10);
			}

			calibrationData[i] = 0;

			for (int x = 0; x < sampleSize; x++)
			{
				calibrationData[i] += analogRead(DATA_PIN);
				log(INFO) << "analogRead: " << calibrationData[i];

				delay(30);
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
		int size = Memory::read(address);
		address += 4;

		log(DEBUG2) << "load size: " << size;

		if (size > 0 )
		{
			//int temp = size;
			calibrationSize = size;
			calibrationStart = Memory::read(address);
			log(DEBUG2) << "calibrationStart : " << calibrationStart;

			address += 4;
			calibrationInterval = Memory::read(address);
			log(DEBUG2) << "calibrationInterval : " << calibrationInterval;

			address += 4;

			//delete[] calibrationData;
		//	calibrationData = new int[calibrationSize];

			for (int i = 0; i < calibrationSize; i++)
			{
				int temp = Memory::read(address);
				address += 4;
				log(DEBUG2) << "loading " << i << "  " << temp;
				calibrationData[i] = temp;
#ifdef __MK20DX256__ // Teensy Compile
				delay(1);
#endif
			}

			return true;
		}

		return false;
	}

	void IRSensor::saveCalibration(int address)
	{
		Memory::write(address, calibrationSize);
		address += 4;
		Memory::write(address, calibrationStart);
		address += 4;
		Memory::write(address, calibrationInterval);
		address += 4;

		for (int i = 0; i < calibrationSize; i++)
		{
			Memory::write(address, calibrationData[i]);
			address += 4;
		}
	}



	float IRSensor::getDistance()
	{
#ifdef __MK20DX256__ // Teensy Compile
		int val = analogRead(DATA_PIN);
#else // PC compile
		// false analog value used while on pc
		int val = rand() % 500;
#endif

		log(DEBUG3) << "Analog Value: " << val;

		for (int i = calibrationSize - 1; i >= 0; i--)
		{
			log(DEBUG4) << "cs: " << calibrationStart << "ci " << calibrationInterval;
			log(DEBUG4) << "calibrationData[ " << i << " ]: " << calibrationData[i] << " , Analog Value: " << val;

			if (val < calibrationData[i])
			{
				int dist = interpolate(calibrationData[i], calibrationData[i + 1],
					i * calibrationInterval + calibrationStart,
					(i + 1) * calibrationInterval + calibrationStart, val);

				log(DEBUG3) << "Measured Distance: " << dist;

				return dist;
			}
		}

		log(DEBUG3) << "Measured Distance*: " << MIN_RANGE;
		return MIN_RANGE;
	}



	void IRSensor::debug()
	{
		getDistance();
	}



	int IRSensor::interpolate(int x1, int x2, int y1, int y2, int x)
	{
		log(DEBUG4) << x1 << " " << x2 << " " << y1 << " " << y2 << " " << x;
 
		return( float(x - x1) / (x2 - x1) * (y2 - y1) + y1);
	}



	void IRSensor::initPins()
	{
#ifdef __MK20DX256__ // Teensy Compile
		pinMode(DATA_PIN, INPUT);
#endif
	}



	void IRSensor::defaultCalibration()
	{
		calibrationSize = 14;
		calibrationInterval = 10;
		calibrationStart = MIN_RANGE;
		delete[] calibrationData;
		calibrationData = new int[calibrationSize];

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
			calibrationData[0] = 550; //20mm
			calibrationData[1] = 422; //30mm
			calibrationData[2] = 336; //40mm
			calibrationData[3] = 271; //50mm
			calibrationData[4] = 216; //60mm
			calibrationData[5] = 172; //70mm
			calibrationData[6] = 119; //80mm
			calibrationData[7] = 88;  //90mm
			calibrationData[8] = 61;  //100mm
			calibrationData[9] = 37;  //120mm
			calibrationData[10] = 19; //130mm
			calibrationData[11] = 13; //140mm
			calibrationData[12] = 7;  //150mm
			calibrationData[13] = 5;  //160mm
		}
	}
}


#include "Motor.h"
#include "Logger.h"

#ifdef __MK20DX256__

namespace Micromouse
{
	Motor::Motor(int fwdPin, int bwdPin, int pwmPin, int fwdEncoderPin, int bwdEncoderPin)
		:
		fwdPin(fwdPin),
		bwdPin(bwdPin),
		pwmPin(pwmPin),
		encoder(Encoder(fwdEncoderPin, bwdEncoderPin))
	{
		initPins();
	}

	void Motor::initPins()
	{
		pinMode(fwdPin, OUTPUT);
		pinMode(bwdPin, OUTPUT);
		pinMode(pwmPin, OUTPUT);
	}

	void Motor::setMovement(float speed)
	{

	}

	void Motor::setMaxSpeed(float maxSpeed)
	{

	}

	void Motor::brake()
	{

	}

	void Motor::coast()
	{

	}

	int Motor::getCounts() const
	{

	}

	int Motor::resetCounts()
	{

	}

	/*
	void Motor::move(int counts, float targetSpeed, float rampTime)
	{
		double speed = 0;

		encoder.write(0);
		
		unsigned long startTime = micros();
		float timePassed = 0;
		bool forward = counts >= 0;
		while ((forward && counts > 0) || (!forward && counts < 0))
		{
			// Calculate timePassed
			timePassed = (micros() - startTime) / 1000000.0f;

			if (rampTime == 0)
			{
				speed = targetSpeed;
			}
			else
			{
				speed = targetSpeed / rampTime * timePassed;
			}

			// Constrain speed < targetSpeed, then give it the same sign as counts.
			speed = speed > targetSpeed ? targetSpeed : speed;
			speed = counts > 0 ? speed : -speed;

			if (speed >= 0)
			{
				digitalWrite(fwdPin, HIGH);
				digitalWrite(bwdPin, LOW);
				analogWrite( pwmPin, (int)(255 * speed) );
			}
			else
			{
				digitalWrite(bwdPin, HIGH);
				digitalWrite(fwdPin, LOW);
				analogWrite( pwmPin, (int)(255 * (-speed)) );
			}

			counts -= encoder.read();
			encoder.write(0);

			//logC(DEBUG1) << "Counts: " << counts;
			//logC(DEBUG1) << "Speed: " << speed;
		}

		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, HIGH);
		analogWrite(pwmPin, 0);
	}
	*/
}

#endif

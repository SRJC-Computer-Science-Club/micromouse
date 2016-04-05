#include "Motor.h"
#include "Logger.h"

namespace Micromouse
{
	Motor::Motor(int fwdPin, int bwdPin, int pwmPin, int fwdEncoderPin, int bwdEncoderPin)
		:
		fwdPin(fwdPin),
		bwdPin(bwdPin),
		pwmPin(pwmPin)
#ifdef __MK20DX256__
		, encoder(Encoder(fwdEncoderPin, bwdEncoderPin))
#endif
	{
		initPins();
	}

	void Motor::initPins()
	{

#ifdef __MK20DX256__
		pinMode(fwdPin, OUTPUT);
		pinMode(bwdPin, OUTPUT);
		pinMode(pwmPin, OUTPUT);
#endif
	}

	void Motor::setMovement(float speed)
	{

#ifdef __MK20DX256__
		if (speed > 1 || speed < -1)
		{
			logC(WARN) << "In setMovement, speed was not between -1 and 1";
			speed = speed >= 0 ? 1 : -1;
		}

		speed *= maxSpeed;

		if (speed >= 0)
		{
			digitalWrite(fwdPin, HIGH);
			digitalWrite(bwdPin, LOW);
			analogWrite(pwmPin, (int)(255 * speed));
		}
		else
		{
			digitalWrite(fwdPin, LOW);
			digitalWrite(bwdPin, HIGH);
			analogWrite(pwmPin, (int)( 255 * (-speed) ));
		}
#endif
	}

	void Motor::setMaxSpeed(float maxSpeed)
	{
#ifdef __MK20DX256__
		if (maxSpeed < 0 || maxSpeed > 1)
		{
			logC(WARN) << "Motor was given a maxSpeed that is not between 0 and 1.";
			maxSpeed = maxSpeed < 0 ? 0 : 1;
		}
		this->maxSpeed = maxSpeed;
#endif
	}

	float Motor::getMaxSpeed() const
	{
		return maxSpeed;
	}

	void Motor::brake()
	{
#ifdef __MK20DX256__
		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, HIGH);
		analogWrite(pwmPin, 0);
#endif
	}

	void Motor::coast()
	{
#ifdef __MK20DX256__
		digitalWrite(fwdPin, LOW);
		digitalWrite(bwdPin, LOW);
		analogWrite(pwmPin, 0);
#endif
	}

	int Motor::getCounts()
	{
#ifdef __MK20DX256__
		return encoder.read();
#endif
		return 0;
	}

	int Motor::resetCounts()
	{
#ifdef __MK20DX256__
		int counts = encoder.read();
		encoder.write(0);
		return counts;
#endif
		return 0;
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

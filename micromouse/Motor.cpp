#include "Motor.h"
#include "Logger.h"

namespace Micromouse
{
	Motor::Motor(int fwdPin, int bwdPin, int pwmPin, int fwdEncoderPin, int bwdEncoderPin):
		fwdPin(fwdPin),
		bwdPin(bwdPin),
		pwmPin(pwmPin)
#ifdef __MK20DX256__ // Teensy Compile
		, encoder(Encoder(fwdEncoderPin, bwdEncoderPin))
#endif
	{
		initPins();
	}



	void Motor::initPins()
	{
#ifdef __MK20DX256__ // Teensy Compile
		pinMode(fwdPin, OUTPUT);
		pinMode(bwdPin, OUTPUT);
		pinMode(pwmPin, OUTPUT);
#endif
	}



	void Motor::setMovement(float speed)
	{
#ifdef __MK20DX256__ // Teensy Compile
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
			analogWrite(pwmPin, (int)(255 * (-speed)));
		}
#endif
	}



	void Motor::setMaxSpeed(float maxSpeed)
	{
#ifdef __MK20DX256__ // Teensy Compile
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
#ifdef __MK20DX256__ // Teensy Compile
		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, HIGH);
		analogWrite(pwmPin, 0);
#endif
	}



	void Motor::coast()
	{
#ifdef __MK20DX256__ // Teensy Compile
		digitalWrite(fwdPin, LOW);
		digitalWrite(bwdPin, LOW);
		analogWrite(pwmPin, 0);
#endif
	}
	


	int Motor::getCounts()
	{
#ifdef __MK20DX256__ // Teensy Compile
		return encoder.read();
#endif
		return 0;
	}



	int Motor::resetCounts()
	{
#ifdef __MK20DX256__ // Teensy Compile
		int counts = encoder.read();
		encoder.write(0);
		return counts;
#endif
		return 0;
	}
}

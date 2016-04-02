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

	void Motor::moveMotor(int counts, float targetSpeed, float rampTime)
	{
		encoder.write(0);

		double speed = 0;
		
		unsigned long startTime = micros();
		float timePassed = 0;
		while (counts != 0)
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

			logC(DEBUG4) << counts;
		}

		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, HIGH);
		analogWrite(pwmPin, 0);
	}

}

#endif

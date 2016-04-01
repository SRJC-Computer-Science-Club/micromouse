#include "Motor.h"

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
		
		unsigned long lastTime = micros();
		unsigned long currentTime = micros();
		while (counts != 0)
		{
			// Calculate deltaTime
			currentTime = micros();
			double deltaTime = (double)(currentTime - lastTime) / 1000000; // 1 Million microseconds in a second.
			lastTime = currentTime;

			counts -= encoder.read();

			// targetSpeed should have the same sign as counts. (+ or -)
			if (counts > 0)
			{
				targetSpeed = targetSpeed > 0 ? targetSpeed : -targetSpeed;
			}
			if (counts < 0)
			{
				targetSpeed = targetSpeed < 0 ? targetSpeed : -targetSpeed;
			}

			// Move speed towards targetSpeed
			speed += (targetSpeed / rampTime) * deltaTime;

			// Constrain speed between -1 and 1
			speed = speed > 1 ? 1 : speed;
			speed = speed < -1 ? -1 : speed;

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
		}
	}

}

#endif

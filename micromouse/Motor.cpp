#include "Motor.h"
#include "Logger.h"
#include "Timer.h"
#include "ArduinoDummy.h"
#include "Memory.h"
#include "RobotIO.h"

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
		loadCalibration();
		initPins();
	}


	
	void Motor::loadCalibration()
	{
		if (pwmPin == MOTOR_LEFT_PWM_PIN)
		{
			minFwdVoltage = Memory::read(Memory::LEFT_FWD_VOLTAGE);
			minBwdVoltage = Memory::read(Memory::LEFT_BWD_VOLTAGE);
		}
		else if (pwmPin == MOTOR_RIGHT_PWM_PIN)
		{
			minFwdVoltage = Memory::read(Memory::RIGHT_FWD_VOLTAGE);
			minBwdVoltage = Memory::read(Memory::RIGHT_BWD_VOLTAGE);
		}
	}



	void Motor::saveCalibration()
	{
		if (pwmPin == MOTOR_LEFT_PWM_PIN)
		{
			Memory::write(Memory::LEFT_FWD_VOLTAGE, minFwdVoltage);
			Memory::write(Memory::LEFT_BWD_VOLTAGE, minBwdVoltage);
		}
		else if (pwmPin == MOTOR_RIGHT_PWM_PIN)
		{
			Memory::write(Memory::RIGHT_FWD_VOLTAGE, minFwdVoltage);
			Memory::write(Memory::RIGHT_BWD_VOLTAGE, minBwdVoltage);
		}
	}



	void Motor::initPins()
	{
		pinMode(fwdPin, OUTPUT);
		pinMode(bwdPin, OUTPUT);
		pinMode(pwmPin, OUTPUT);
	}



	void Motor::calibrate()
	{
		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, LOW);
		minFwdVoltage = calibrateMinVoltage() + 1;

		digitalWrite(fwdPin, LOW);
		digitalWrite(bwdPin, HIGH);
		minBwdVoltage = calibrateMinVoltage() + 1;

		digitalWrite(fwdPin, LOW);
		digitalWrite(bwdPin, LOW);

		saveCalibration();
	}



	int Motor::calibrateMinVoltage()
	{
		Timer timer = Timer();
		int voltage = 32;
		bool timedOut = false;
		while (voltage > 0 && !timedOut)
		{
			voltage--;
			analogWrite(pwmPin, voltage);

			float waitTime = 0;
			timer.start();
			resetCounts();
			while (getCounts() < 20 && getCounts() > -20 && !timedOut)
			{
				waitTime += timer.getDeltaTime();
				Serial.println(waitTime);
				if (waitTime >= CALIBRATION_TIMEOUT_SEC)
				{
					timedOut = true;
				}
			}
		}

		return voltage;
	}



	void Motor::setMovement(float speed)
	{
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
			setVoltage((int)(256 * speed), true);
		}
		else
		{
			digitalWrite(fwdPin, LOW);
			digitalWrite(bwdPin, HIGH);
			setVoltage((int)(256 * (-speed)), false);
		}
	}


	
	void Motor::setVoltage(int voltage, bool fwd)
	{
		if (voltage > 0)
		{
			if (fwd)
			{
				if (voltage < minFwdVoltage)
				{
					voltage = minFwdVoltage;
				}
			}
			else
			{
				if (voltage < minBwdVoltage)
				{
					voltage = minBwdVoltage;
				}
			}
		}

		analogWrite(pwmPin, voltage);
	}



	void Motor::setMaxSpeed(float maxSpeed)
	{
		if (maxSpeed < 0 || maxSpeed > 1)
		{
			logC(WARN) << "Motor was given a maxSpeed that is not between 0 and 1.";
			maxSpeed = maxSpeed < 0 ? 0 : 1;
		}
		this->maxSpeed = maxSpeed;
	}



	float Motor::getMaxSpeed() const
	{
		return maxSpeed;
	}



	void Motor::brake()
	{
		digitalWrite(fwdPin, HIGH);
		digitalWrite(bwdPin, HIGH);
		analogWrite(pwmPin, 0);
	}



	void Motor::coast()
	{
		digitalWrite(fwdPin, LOW);
		digitalWrite(bwdPin, LOW);
		analogWrite(pwmPin, 0);
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

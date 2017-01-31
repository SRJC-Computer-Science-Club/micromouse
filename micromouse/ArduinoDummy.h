#pragma once

namespace Micromouse
{
#ifndef __MK20DX256__ // If NOT on Teensy

	enum PinMode
	{
		INPUT, OUTPUT
	};

	enum PinValue
	{
		LOW, HIGH
	};

	void pinMode(int pin, PinMode mode) { }
	void digitalWrite(int pin, PinValue value) { }
	void analogWrite(int pin, int value) { }


	class SERIAL
	{
	public:
		void println(float x) {}
	};

	SERIAL Serial = SERIAL();

#endif
}
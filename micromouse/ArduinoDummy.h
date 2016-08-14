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
		void println(char* x) {}
		void println(float x) {}
		void println(float x, int y) {}
		void print(char* x) {}
		void print(float x) {}
		void print(float x, int y) {}
	};

	SERIAL Serial = SERIAL();

#endif
}
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

	static void pinMode(int pin, PinMode mode) { }
	static void digitalWrite(int pin, PinValue value) { }
	static void analogWrite(int pin, int value) { }

	static void delay(int x) { }

	class SERIAL
	{
	public:
		void println(const char* x) {}
		void println(float x) {}
		void println(float x, int y) {}
		void print(const char* x) {}
		void print(float x) {}
		void print(float x, int y) {}
	};

	static SERIAL Serial = SERIAL();

#endif
}
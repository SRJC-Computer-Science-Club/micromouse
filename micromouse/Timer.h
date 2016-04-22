#pragma once

#include <chrono>



namespace Micromouse
{
	class Timer
	{
	public:
		Timer();

		void start();
		float getDeltaTime();

	private:
#ifdef __MK20DX256__ // Teensy Compile
#else // PC compile
		long micros();

		typedef std::chrono::steady_clock::time_point time_point;
		time_point initialTime = std::chrono::high_resolution_clock::now();
#endif

		long lastMicros;
	};
}
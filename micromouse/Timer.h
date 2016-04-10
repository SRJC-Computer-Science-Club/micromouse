#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	void start();
	float getDeltaTime();
private:
	long lastMicros;

#ifndef __MK20DX256__
	// If on PC
	long micros();

	typedef std::chrono::steady_clock::time_point time_point;
	time_point initialTime = std::chrono::high_resolution_clock::now();
#endif
};

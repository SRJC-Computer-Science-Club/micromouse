/*********************************\
File:			PIDController.h
Creation date:	4/5/2016

Author Names:	Joshua Murphy
Yyekalo Aberha

Author GitHub:	joshuasrjc
yyekalo
\*********************************/

#pragma once
#ifndef __MK20DX256__
#include <chrono>
#endif

namespace Micromouse
{
	// This class uses PID control to determine the amount of correction needed
	class PIDController
	{
	public:
		// Sets the P, I, and D constants for the controller.
		PIDController(float P, float I, float D, float maxIntegralError = 500.0f )
			: P(P), I(I), D(D), maxIntegralError(maxIntegralError) {}

		// Starts the controller with an initial error, and resets the total error.
		// MUST be called before calling getCorrection().
		void start(float initialError);

		// Returns the error correction.
		// start() MUST be called before calling this function.
		float getCorrection(float currentError);

		float getI() const;

		// Sets the P, I, and D constants for the controller.
		void setConstants(float P, float I, float D);

	private:
		float getDeltaTime();

#ifndef __MK20DX256__
		// If on PC
		long micros();

		typedef std::chrono::steady_clock::time_point time_point;
		time_point initialTime = std::chrono::high_resolution_clock::now();
#endif

		bool started = false;
		float totalError = 0;
		float lastError = 0;
		float maxIntegralError;

		float P;
		float I;
		float D;

		long lastTime;
	};
}
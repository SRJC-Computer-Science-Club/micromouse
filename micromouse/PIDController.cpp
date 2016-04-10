/*********************************\
File:			PIDController.cpp
Creation date:	4/5/2016

Author Names:	Joshua Murphy
				Yyekalo Aberha

Author GitHub:	joshuasrjc
				yyekalo
\*********************************/

#include "PIDController.h"
#include <assert.h>
#include "Logger.h"
#ifndef __MK20DX256__
#include <iostream>
#endif



namespace Micromouse
{
	void PIDController::start(float initialError)
	{
		totalError = 0;
		lastError = initialError;
		lastTime = micros();

		started = true;
	}

	float PIDController::getCorrection(float currentError)
	{
		assert(started);

		float deltaTime = getDeltaTime();

		totalError += currentError * deltaTime;
		
		//totalError is bounded between -MAX_I_ERROR and +MAX_I_ERROR
		totalError = totalError < -MAX_I_ERROR ? -MAX_I_ERROR : totalError;
		totalError = totalError > MAX_I_ERROR ? MAX_I_ERROR : totalError;

		float pCorrection = P * currentError;
		float iCorrection = I * totalError;
		float dCorrection = D * (currentError - lastError);

		float sum = pCorrection + iCorrection + dCorrection;
		sum /= 1000.0f;

		//Sum is bounded between -1 and 1
		sum = sum < -1 ? -1 : sum;
		sum = sum > 1 ? 1 : sum;

		return sum;
	}

	float PIDController::getI() const
	{
		return totalError;
	}

	void PIDController::setConstants(float P, float I, float D)
	{
		this->P = P;
		this->I = I;
		this->D = D;
	}

	float PIDController::getDeltaTime()
	{
		long currentTime = micros();
		float deltaTime = (currentTime - lastTime) / 1000000.0f; //1,000,000 microseconds in a second.
		lastTime = currentTime;
		return deltaTime;
	}

#ifndef __MK20DX256__
	long PIDController::micros()
	{
		using namespace std::chrono;
		
		return duration_cast<microseconds>(high_resolution_clock::now() - initialTime).count();
	}
#endif

}



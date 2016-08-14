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

#ifdef __MK20DX256__ // Teensy compile
#else // PC compile
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

		//if (currentError < 5.0f && currentError > -5.0f)
		{
			totalError += currentError * deltaTime;
		}
		
		//totalError is bounded between -MAX_I_ERROR and +MAX_I_ERROR
		totalError = totalError < -maxIntegralError ? -maxIntegralError : totalError;
		totalError = totalError > maxIntegralError ? maxIntegralError : totalError;

		float pCorrection = P * currentError;
		float iCorrection = I * totalError;
		float dCorrection = D * (currentError - lastError);

		lastError = 0.9 * lastError + 0.1 * currentError; 

		pCorrection /= 1000;
		iCorrection /= 1000;
		dCorrection /= 1000;

		lastP_Correction = pCorrection;
		lastI_Correction = iCorrection;
		lastD_Correction = dCorrection;

		float sum = pCorrection + iCorrection + dCorrection;

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



#ifdef __MK20DX256__ // Teensy compile
#else // PC compile
	long PIDController::micros()
	{
		using namespace std::chrono;
		
		return duration_cast<microseconds>(high_resolution_clock::now() - initialTime).count();
	}
#endif
}



#pragma once
#include "Logger.h"

namespace Micromouse {


	template<typename T>
	class Recorder
	{
	public:
		Recorder(int size = 1000, int dimension = 1);
		~Recorder();

		bool addValue(T val, int dimension);
		void print();

		const int SIZE, DIMENSION;

		int* ind;

		T** arrs;





	};


	template<typename T>
	Recorder<T>::Recorder(int size, int dimension) :
		SIZE(size),
		DIMENSION(dimension)
	{
		ind = new int [DIMENSION];
		arrs = new T* [DIMENSION];
		
		for (size_t i = 0; i < DIMENSION; i++)
		{
			arrs[i] = new T[SIZE];
			ind[i] = 0;
		}
	}


	template<typename T>
	Recorder<T>::~Recorder()
	{
		for (size_t i = 0; i < DIMENSION; i++)
		{
			delete[] arrs[i];
		}

		delete[] arrs;
		delete[] ind;
	}


	template<typename T>
	bool Recorder<T>::addValue(T val, int dimension)
	{
		if (ind[dimension] < SIZE)
		{
			arrs[dimension][ind[dimension]++] = val;
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	void Recorder<T>::print()
	{
		buttonFlag = false;
#ifdef __MK20DX256__ // Teensy Compile
		while (!buttonFlag)
		{
			delay(10);
		}

		for (int i = 0; i < ind[0]; i++)
		{
			for (int j = 0; j < DIMENSION - 1; j++)
			{
				Serial.print(arrs[j][i]);
				Serial.print(", ");
			}
			Serial.println(arrs[DIMENSION-1][i]);
			delay(1);
		}
#endif
		buttonFlag = false;
	}
}
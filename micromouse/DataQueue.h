#pragma once

//A class that holds data in an array that functions like a queue.
//First in, first out data structure.
//It has a maximum size.
//Once the max size is reached, it will start overwritting the oldest data.
class DataQueue
{
public:
	DataQueue(int maxSize);

	//Push an element into the queue.
	//Max size must be greater than zero.
	void push(float element);

	//Returns the oldest element in the queue.
	//Size must be greater than zero.
	float peek() const;

	//Returns the oldest element in the queue.
	//Removes that element from the queue.
	//Size must be greater than zero.
	float pop();



	//Returns the current number of elements in the queue.
	int getSize() const;

	//Returns the maximum number of elements in the queue.
	int getMaxSize() const;

	//Returns true if there are no elements in the queue.
	bool isEmpty() const;

	//Returns true if the number of elements in the queue is equal to the max size.
	bool isFull() const;
	
private:
	int maxSize;
	int size = 0;
	float* data;
	int tailIndex = 0;
	int headIndex = 0;
};

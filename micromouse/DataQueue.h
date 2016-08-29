#pragma once

//A class that holds data in an array that functions like a queue.
//First in, first out data structure.
//It has a maximum capacity.
//Once the capacity is reached, it will start overwritting the oldest data.
class DataQueue
{
public:
	//Sets the maximum number of elements that can be stored in the queue.
	DataQueue(int maxSize);

	DataQueue(const DataQueue& queue);
	~DataQueue();

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

	void clear();



	//Returns the current number of elements in the queue.
	int getSize() const;

	//Returns the maximum number of elements in the queue.
	int getCapacity() const;

	//Returns true if there are no elements in the queue.
	bool isEmpty() const;

	//Returns true if the number of elements in the queue is equal to the max size.
	bool isFull() const;



	//Returns the average of all the elements in the queue.
	float getAverage() const;
	
private:
	int capacity;
	int size = 0;
	float* data;
	int tailIndex = 0;
	int headIndex = 0;
};

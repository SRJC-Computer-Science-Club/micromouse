#include "DataQueue.h"
#include <assert.h>

DataQueue::DataQueue(int capacity)
	: capacity(capacity)
{
	data = new float[capacity];
}

DataQueue::DataQueue(const DataQueue& queue)
{
	capacity = queue.capacity;
	size = queue.size;
	tailIndex = queue.tailIndex;
	headIndex = queue.headIndex;

	data = new float[capacity];
	for (int i = 0; i < capacity; i++)
	{
		data[i] = queue.data[i];
	}
}

DataQueue::~DataQueue()
{
	delete[] data;
}

void DataQueue::push(float element)
{
	assert(capacity > 0); //Cannot push to a DataQueue with capacity <= 0.

	data[headIndex] = element;

	size++;
	if (size > capacity)
	{
		size = capacity;

		tailIndex++;
		if (tailIndex >= capacity)
		{
			tailIndex = 0;
		}
	}

	headIndex++;
	if (headIndex >= capacity)
	{
		headIndex = 0;
	}
}

float DataQueue::peek() const
{
	assert(!isEmpty()); //Cannot peek at an empty DataQueue.

	return data[tailIndex];
}

float DataQueue::pop()
{
	assert(!isEmpty()); //Cannot pop from an empty DataQueue.

	float element = data[tailIndex];

	size--;

	tailIndex++;
	if (tailIndex >= capacity)
	{
		tailIndex = 0;
	}

	return element;
}

void DataQueue::clear()
{
	size = 0;
	tailIndex = 0;
	headIndex = 0;
}

int DataQueue::getSize() const
{
	return size;
}

int DataQueue::getCapacity() const
{
	return capacity;
}

bool DataQueue::isEmpty() const
{
	return size == 0;
}

bool DataQueue::isFull() const
{
	return size == capacity;
}

float DataQueue::getAverage() const
{
	float avg = 0;
	for (int i = 0; i < size; i++)
	{
		avg += data[(i + headIndex) % capacity];
	}
	avg /= size;
	return avg;
}

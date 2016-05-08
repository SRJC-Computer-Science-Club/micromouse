#include "DataQueue.h"
#include <assert.h>

DataQueue::DataQueue(int maxSize)
	: maxSize(maxSize)
{
	data = new float[maxSize];
}

DataQueue::DataQueue(const DataQueue& queue)
{
	maxSize = queue.maxSize;
	size = queue.size;
	tailIndex = queue.tailIndex;
	headIndex = queue.headIndex;

	data = new float[maxSize];
	for (int i = 0; i < maxSize; i++)
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
	assert(maxSize > 0); //Cannot push to a DataQueue with maxSize <= 0.

	data[headIndex] = element;

	size++;
	if (size > maxSize)
	{
		size = maxSize;

		tailIndex++;
		if (tailIndex >= maxSize)
		{
			tailIndex = 0;
		}
	}

	headIndex++;
	if (headIndex >= maxSize)
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
	if (tailIndex >= maxSize)
	{
		tailIndex = 0;
	}

	return element;
}

int DataQueue::getSize() const
{
	return size;
}

int DataQueue::getMaxSize() const
{
	return maxSize;
}

bool DataQueue::isEmpty() const
{
	return size == 0;
}

bool DataQueue::isFull() const
{
	return size == maxSize;
}

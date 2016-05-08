#pragma once

class DataQueue
{
public:
	DataQueue(int maxSize);

	void push(float element);
	float peek() const;
	float pop();

	int getSize() const;
	int getMaxSize() const;
	bool isEmpty() const;
	bool isFull() const;
	
private:
	int maxSize;
	int size = 0;
	float* data;
	int tailIndex = 0;
	int headIndex = 0;
};

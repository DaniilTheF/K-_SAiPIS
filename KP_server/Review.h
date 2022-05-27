#pragma once
#include "CheckNumb.h"

class Review
{
private:
	char* log;
	int counter;
	int* review;
public:
	Review();
	Review(char*, int*, int);
	Review(const Review&);

	char* getLog() { return this->log; }
	int getCounter() { return this->counter; }
	const int* getReview() { return this->review; }

	void operator=(const Review&);

	~Review();
};
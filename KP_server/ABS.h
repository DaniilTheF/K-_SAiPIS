#pragma once
#include "Connection.h"
#include "ExecutionProc.h"
class ABS 
{
public:
	virtual void Read() = 0;
	virtual void Write() = 0;
	virtual void ReadReview() = 0;
	virtual void WriteReview() = 0;

};
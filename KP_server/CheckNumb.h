#pragma once
#include "Connection.h"
#include <typeinfo>

class CheckNumb
{
public:
	void setLine(char*&, Connection&);
	void copyLine(char*&, const char*);
	int Datacheck(int min, int max, Connection&);
	double Datacheck(double min, double max, Connection&);
	template<class T>
	T check_type(T a, Connection&);
};

static CheckNumb serv;
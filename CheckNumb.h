#pragma once
#include "Connection.h"

class CheckNumb
{
public:
	void setStr(Connection&);
	void setLine(int counter, char symbol);
	int checkDatai(Connection&);
	double checkDatad(Connection&);
	void encription(Connection&);
};

static CheckNumb klient;
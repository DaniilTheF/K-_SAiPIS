#pragma once
#include "CheckNumb.h"

class ProductRange
{
private:
	char* info;
	char* type;
	char* demand;
	double sum;
	int quantity;
	double expectation;
	double income;
public:
	ProductRange();
	ProductRange(char* intell, char* type, char* curr,
		double sum, int num_of_moth, double percent, double income);
	ProductRange(const ProductRange& obj);

	char* getInfo() { return this->info; }
	char* getType() { return this->type; }
	char* getDemand() { return this->demand; }
	double getSum() { return this->sum; }
	int getQuantity() { return this->quantity; }
	double getExpectation() { return this->expectation; }
	double getIncom() { return this->income; }

	void setInfo(char*);
	void setType(char*);
	void setDemand(char*);
	void setIncom(double, int, double);

	void operator=(const ProductRange& obj);
	~ProductRange();
};
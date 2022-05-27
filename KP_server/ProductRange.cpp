#include "ProductRange.h"

ProductRange::ProductRange() : info(0), type(0),
demand(0), sum(0), quantity(0), expectation(0), income(0)
{
	/*cout << "Конструктор без параметров Investment_object" << endl;*/
}

ProductRange::ProductRange(char* intell, char* type, char* curr, double sum, int quantity, double expectation, double income)
{
	serv.copyLine(this->info, intell);
	serv.copyLine(this->type, type);
	serv.copyLine(this->demand, curr);
	this->sum = sum;
	this->quantity = quantity;
	this->expectation = expectation;
	this->income = income;
	/*cout << "Коструктор с параметрами Investment_object" << endl;*/
}

ProductRange::ProductRange(const ProductRange& obj)
{
	serv.copyLine(this->info, obj.info);
	serv.copyLine(this->type, obj.type);
	serv.copyLine(this->demand, obj.demand);
	this->sum = obj.sum;
	this->quantity = obj.quantity;
	this->expectation = obj.expectation;
	this->income = obj.income;
	/*cout << "Коструктор копирования Investment_object" << endl;*/
}

void ProductRange::setInfo(char* info)
{
	delete[] this->info;
	serv.copyLine(this->info, info);
}

void ProductRange::setType(char* type)
{
	delete[] this->type;
	serv.copyLine(this->type, type);
}
void ProductRange::setDemand(char* demand)
{
	delete[] this->demand;
	serv.copyLine(this->demand, demand);
}

void ProductRange::setIncom(double sum, int quantity, double expectation)
{
	this->sum = sum;
	this->quantity = quantity;
	this->expectation = expectation;
	this->income = (sum * quantity) - expectation;
}

void ProductRange::operator=(const ProductRange& obj)
{
	delete[] this->info;
	delete[] this->type;

	delete[] this->demand;
	serv.copyLine(this->info, obj.info);
	serv.copyLine(this->type, obj.type);
	serv.copyLine(this->demand, obj.demand);
	this->sum = obj.sum;
	this->quantity = obj.quantity;
	this->expectation = obj.expectation;
	this->income = obj.income;
}

ProductRange::~ProductRange()
{
	delete[] this->info;
	delete[] this->type;
	delete[] this->demand;
	/*cout << "Деструктор класса Investment_object" << endl;*/
}
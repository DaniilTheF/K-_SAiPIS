#include "Review.h"

Review::Review() : log(0), counter(0), review(0)
{
	/*cout << "Конструктор без параметров Opinion" << endl;*/
}

Review::Review(char* log, int* opinion, int count)
{
	serv.copyLine(this->log, log);
	this->counter = count;
	this->review = new int[this->counter];
	for (int i = 0; i < this->counter; i++)
		this->review[i] = opinion[i];
	/*cout << "Конструктор с параметрами Opinion" << endl;*/
}

Review::Review(const Review& obj)
{
	serv.copyLine(this->log, obj.log);
	this->counter = obj.counter;
	this->review = new int[this->counter];
	for (int i = 0; i < this->counter; i++)
		this->review[i] = obj.review[i];
	/*cout << "Конструктор копирования Opinion" << endl;*/
}

void Review::operator=(const Review& obj)
{
	delete[] this->log;
	delete[] this->review;
	serv.copyLine(this->log, obj.log);
	this->counter = obj.counter;
	review = new int[this->counter];
	for (int i = 0; i < this->counter; i++)
		this->review[i] = obj.review[i];
}

Review::~Review()
{
	delete[] log;
	delete[] review;
	/*cout << "Деструктор Opinion" << endl;*/
}

#include "CheckNumb.h"

void CheckNumb::setStr(Connection& connect)
{
	char* str = new char[100];
	do {
		cin.clear(); cin.getline(str, 100, '\n');
		if (strlen(str) == 0)
		{
			cout << "Пустая строка, введите данные еще раз: ";
		}
	} while (strlen(str) == 0);
	connect.SendStr(str);
	delete[] str;
}

void CheckNumb::setLine(int counter, char symbol)
{
	for (int i = 0; i < counter; i++)
	{
		cout << symbol;
	}
}

int CheckNumb::checkDatai(Connection& connect)
{
	int min = connect.RecvInt();
	int max = connect.RecvInt();
	klient.setStr(connect);
	int x = connect.RecvInt();
	while (x < min || x > max)
	{
		cout << "Нет такого варианта, введи еще раз: ";
		klient.setStr(connect);
		x = connect.RecvInt();
	}
	return x;
}

double CheckNumb::checkDatad(Connection& connect)
{
	double min = connect.RecvDouble();
	double max = connect.RecvDouble();
	setStr(connect);
	double x = connect.RecvDouble();
	while (x < min || x > max)
	{
		cout << "Нет такого варианта, введи еще раз: ";
		setStr(connect);
		x = connect.RecvDouble();
	}
	return x;
}

void CheckNumb::encription(Connection& connect)
{
	char* a = new char[100];
	int i;
	do {
		for (i = 0; (a[i] = _getch()) != '\r';)
		{
			if (a[i] == '\b' && i != 0)
			{
				printf("\b \b");
				i--;
			}
			else if (a[i] != '\b')
			{
				printf("*");
				i++;
			}
		}
		cout << endl;
		a[i] = '\0';
		if (strlen(a) == 0)
			cout << "Пустая строка, введите данные еще раз: ";
	} while (strlen(a) == 0);
	connect.SendStr(a); delete[] a;
}

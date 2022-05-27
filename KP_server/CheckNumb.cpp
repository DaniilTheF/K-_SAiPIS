#include "CheckNumb.h"

void CheckNumb::setLine(char*& buf, Connection& connect)
{
	char* str = new char[100];
	connect.RecvStr(str);
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == ' ')
			str[i] = '_';
	copyLine(buf, str);
	delete[] str;
}

void CheckNumb::copyLine(char*& data_1, const char* data_2)
{
	try
	{
		data_1 = new char[strlen(data_2) + 1];
	}
	catch (bad_alloc err)
	{
		cout << "Error: bad_alloc" << endl;
		exit(1);
	}
	strcpy(data_1, data_2);
}

int CheckNumb::Datacheck(int min, int max, Connection& connect)
{
	connect.SendInt(min);
	connect.SendInt(max);
	int x = check_type(2, connect);
	connect.SendInt(x);
	while (x < min || x > max)
	{
		x = check_type(2, connect);
		connect.SendInt(x);
	}
	return x;
}


double CheckNumb::Datacheck(double min, double max, Connection& connect)
{
	connect.SendDouble(min);
	connect.SendDouble(max);
	double x = check_type(2.0, connect);
	connect.SendDouble(x);
	while (x < min || x > max)
	{
		x = check_type(2.0, connect);
		connect.SendDouble(x);
	}
	return x;
}

template<class T>
T CheckNumb::check_type(T a, Connection& connect) {
	if (typeid(a) == typeid(int)) {
		int x, k = 0;
		char* l = new char[100];
		setLine(l, connect);
		for (int i = 0; l[i] != '\0'; i++)
		{
			if (isdigit(l[i]))
				k++;
		}
		if (strlen(l) != k || (l[0] == '0' && strlen(l) > 1))
			x = -1;
		else
			x = atoi(l);
		delete[] l;
		return x;

	}
	else {
		int k = 0, z = 0;
		double x;
		char* l = new char[100];
		setLine(l, connect);
		for (int i = 0; l[i] != '\0'; i++)
		{
			if (isdigit(l[i]))
				k++;
			if (l[i] == ',')
				z++;
		}
		if (strlen(l) != (k + z) || (l[0] == '0' && l[1] == '0') || l[0] == ',' || z > 1)
			x = -1;
		else x = atof(l);
		delete[] l;
		return x;
	}
}

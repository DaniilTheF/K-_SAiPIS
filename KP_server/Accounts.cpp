#include "Accounts.h"

Man::Man() : surname(0), name(0), patronymic(0)
{
	/*cout << "Конструктор без параметров Human" << endl;;*/
}

Man::Man(char* surname, char* name, char* patronymic)
{
	serv.copyLine(this->surname, surname);
	serv.copyLine(this->name, name);
	serv.copyLine(this->patronymic, patronymic);
	/*cout << "Конструктор с параметрами Human" << endl;*/
}

Man::Man(const Man& obj)
{
	serv.copyLine(this->surname, obj.surname);
	serv.copyLine(this->name, obj.name);
	serv.copyLine(this->patronymic, obj.patronymic);
	/*cout << "Коструктор копирования Human" << endl;*/
}

Man::~Man()
{
	delete[] surname;
	delete[] name;
	delete[] patronymic;
	/*cout << "Деструктор Human" << endl;*/
}

void Man::operator=(const Man& obj)
{
	delete[] this->surname; delete[] this->name; delete[] this->patronymic;
	serv.copyLine(this->surname, obj.surname);
	serv.copyLine(this->name, obj.name);
	serv.copyLine(this->patronymic, obj.patronymic);
}

User::User() : Man(), status(0), password(0), login(0)
{
	/*cout << "Конструктор без параметров User" << endl;*/
}

User::User(char* surname, char* name, char* patronymic,
	const char* status, char* login, char* password) : Man(surname, name, patronymic)
{
	serv.copyLine(this->status, status);
	serv.copyLine(this->login, login);
	serv.copyLine(this->password, password);
	/*cout << "Конструктор с параметрами Human" << endl;*/
}

User::User(const User& obj) : Man(obj)
{
	serv.copyLine(this->status, obj.status);
	serv.copyLine(this->login, obj.login);
	serv.copyLine(this->password, obj.password);
	/*cout << "Конструктор копирования User" << endl;*/
}

User::~User()
{
	delete[] status;
	delete[] login;
	delete[] password;
	//cout << "Деструктор User" << endl;
}

void User::operator=(const User& obj)
{
	Man::operator=(obj);
	delete[] this->status; delete[] this->login; delete[] this->password;
	serv.copyLine(this->status, obj.status);
	serv.copyLine(this->login, obj.login);
	serv.copyLine(this->password, obj.password);
}
#pragma once
#include "Connection.h"
#include "CheckNumb.h"

class Man
{
private:

	char* surname;
	char* name;
	char* patronymic;

public:

	Man();
	Man(char*, char*, char*);
	Man(const Man&);
	~Man();

	char* getSurname() { return this->surname; }
	char* getName() { return this->name; }
	char* getPatronymic() { return this->patronymic; }

	void operator=(const Man&);

};

class User : public Man
{
private:

	char* status;
	char* login;
	char* password;

public:

	User();
	User(char*, char*, char*, const char*, char*, char*);
	User(const User&);
	~User();

	char* getStatus() { return this->status; }
	char* getLogin() { return this->login; }
	char* getPassword() { return this->password; }

	void operator=(const User&);


};


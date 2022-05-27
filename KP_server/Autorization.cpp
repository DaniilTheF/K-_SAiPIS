#include "Autorization.h"

void Autorization::Read()
{
	cout << "Reading Users" << endl;
	ifstream fin("Users.txt");
	char* surname = new char[100]; char* name = new char[100];
	char* patronymic = new char[100]; char* status = new char[100];
	char* login = new char[100]; char* password = new char[100];
	while (fin >> status >> login >> password >> surname >> name >> patronymic)
	{
		for (int i = 0; login[i] != '\0'; i++)
			login[i] += 5;
		for (int j = 0; password[j] != '\0'; j++)
			password[j] += 10;
		User obj(surname, name, patronymic, status, login, password);
		this->vectUser.push_back(obj);
	}
	delete[] surname; delete[] name; delete[] patronymic;
	delete[] status; delete[] login; delete[] password;
	fin.close();
}

void Autorization::Add(const char* status, Connection& connect)
{
	cout << "Add Accounts" << status << ">" << endl;

	char* surname = new char[100]; char* name = new char[100];
	char* patronymic = new char[100]; char* login = new char[100];
	char* password = new char[100];

	connect.SendStr(status);

	serv.setLine(surname, connect);
	serv.setLine(name, connect);
	serv.setLine(patronymic, connect);

	setLogin(login, connect);

	serv.setLine(password, connect);
	User obj(surname, name, patronymic, status, login, password);
	this->vectUser.push_back(obj);

	delete[] surname; delete[] name; delete[] patronymic;
	delete[] login; delete[] password;
}

void Autorization::setLogin(char*& login, Connection& connect)
{
	int k;
	char* buf = new char[100];
	char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm._-1234567890";
	do {
		k = 0;
		serv.setLine(buf, connect);
		if (strlen(buf) < 6)
		{
			k = 1;
		}
		else
		{
			for (register int i = 0; buf[i] != '\0'; i++)
			{
				k = 2;
				for (register int j = 0; symbols[j] != '\0'; j++)
				{
					if (buf[i] == symbols[j])
					{
						k = 0;
						break;
					}
				}
				if (k == 2)
					break;
			}
			if (k == 0)
			{
				for (vector<User>::iterator it = vectUser.begin(); it != vectUser.end(); it++)
				{
					if (strcmp(it->getLogin(), buf) == 0)
					{
						k = 3;
						break;
					}
				}
			}
		}
		connect.SendInt(k);
	} while (k != 0);
	strcpy(login, buf);
	delete[] buf;
}

void Autorization::Output(Connection& connect)
{
	cout << "Output Accounts" << endl;
	connect.SendInt(vectUser.size());
	for (vector<User>::iterator it = this->vectUser.begin(); it != this->vectUser.end(); it++)
	{
		connect.SendStr(it->getStatus());
		connect.SendStr(it->getLogin());

		connect.SendStr(UserStatus);
		if (strcmp(UserStatus, "MAIN") == 0)
			connect.SendStr(it->getPassword());

		connect.SendStr(it->getSurname());
		connect.SendStr(it->getName());
		connect.SendStr(it->getPatronymic());
	}
}

void Autorization::DeleteAcc(Connection& connect)
{
	cout << "Deleting Accounts" << endl;
	int choice;
	do {
		Output(connect);
		choice = serv.Datacheck(0, vectUser.size(), connect);
		if (choice != 0)
		{
			if (strcmp(vectUser[choice - 1].getLogin(), UserLogin) == 0)
			{
				connect.SendInt(1);
			}
			else if (strcmp(UserStatus, "ADMIN") == 0 && (strcmp(vectUser[choice - 1].getStatus(), "ADMIN") == 0 || strcmp(vectUser[choice - 1].getStatus(), "MAIN") == 0))
			{
				connect.SendInt(2);
			}
			else
			{
				connect.SendInt(3);
				int del = serv.Datacheck(1, 2, connect);

				if (del == 1)
				{
					if (vectreview.size() > 0 && strcmp(vectUser[choice - 1].getStatus(), "EXPERT") == 0)
					{
						for (int i = 0; i < vectreview.size(); i++)
						{
							if (strcmp(vectreview[i].getLog(), vectUser[choice - 1].getLogin()) == 0)
								vectreview.erase(vectreview.cbegin() + i);
						}
					}
					this->vectUser.erase(vectUser.cbegin() + (choice - 1));

				}
			}
		}
	} while (choice != 0);
}

void Autorization::Write()
{
	cout << "Write Accounts" << endl;
	ofstream fout("Users.txt", ios_base::trunc);
	char* login = new char[100];
	char* password = new char[100];
	for (vector<User>::iterator it = this->vectUser.begin(); it != this->vectUser.end(); it++)
	{
		strcpy(login, it->getLogin());
		for (int i = 0; login[i] != '\0'; i++)
			login[i] -= 5;
		strcpy(password, it->getPassword());
		for (int j = 0; password[j] != '\0'; j++)
			password[j] -= 10;
		fout << it->getStatus() << " " << login << " " << password << " "
			<< it->getSurname() << " " << it->getName() << " " << it->getPatronymic() << endl;
	}
	delete[] login;
	delete[] password;
	fout.close();
}

int Autorization::Authorizatio(Connection& connect)
{
	cout << "Authorization" << endl;
	int result = 0;
	char* login = new char[100];
	char* password = new char[100];
	while (1)
	{
		serv.setLine(login, connect);
		serv.setLine(password, connect);
		for (int i = 0; i < vectUser.size(); i++)
		{
			if (strcmp(login, vectUser[i].getLogin()) == 0 && strcmp(password, vectUser[i].getPassword()) == 0)
			{
				serv.copyLine(UserStatus, vectUser[i].getStatus());
				serv.copyLine(UserLogin, vectUser[i].getLogin());
				if (strcmp(vectUser[i].getStatus(), "ADMIN") == 0 || strcmp(vectUser[i].getStatus(), "MAIN") == 0)
				{
					result = 1;
					break;
				}
				else if (strcmp(vectUser[i].getStatus(), "EXPERT") == 0)
				{
					result = 2;
					break;
				}
				else { result = 3; break; }
			}
		}
		connect.SendInt(result);
		if (result == 0)
		{
			if (serv.Datacheck(1, 2, connect) == 2)
				break;
		}
		else break;
	}
	delete[] login;
	delete[] password;
	return result;
}


void Autorization::ReadReview()
{
	cout << "Read Review" << endl;
	char* log = new char[100];
	int pol;
	ifstream fin("Review.txt");
	if (fin >> log >> pol)
	{
		int* opinion = new int[pol];
		fin.seekg(0, ios_base::beg);
		while (fin >> log >> pol)
		{
			for (int i = 0; i < pol; i++)
				fin >> opinion[i];

			Review obj(log, opinion, pol);
			vectreview.push_back(obj);

		}
		delete[] opinion;
	}
	delete[] log;
	fin.close();
}

void Autorization::WriteReview()
{
	cout << "Write Review" << endl;
	if (this->vectreview.size() > 0)
	{
		ofstream fout("Review.txt", ios_base::trunc);
		for (vector<Review>::iterator it = vectreview.begin(); it != vectreview.end(); it++)
		{
			fout << it->getLog() << " " << it->getCounter();;
			for (int i = 0; i < it->getCounter(); i++)
				fout << " " << it->getReview()[i];
			fout << endl;
		}
		fout.close();
	}
}
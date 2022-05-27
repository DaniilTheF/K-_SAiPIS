#include "ExecutionProc.h"

//void ExecutionProc::ReadAcc()
//{
//	cout << "Reading Users" << endl;
//	ifstream fin("Users.txt");
//	char* surname = new char[100]; char* name = new char[100];
//	char* patronymic = new char[100]; char* status = new char[100];
//	char* login = new char[100]; char* password = new char[100];
//	while (fin >> status >> login >> password >> surname >> name >> patronymic)
//	{
//		for (int i = 0; login[i] != '\0'; i++)
//			login[i] += 5;
//		for (int j = 0; password[j] != '\0'; j++)
//			password[j] += 10;
//		User obj(surname, name, patronymic, status, login, password);
//		this->vectUser.push_back(obj);
//	}
//	delete[] surname; delete[] name; delete[] patronymic;
//	delete[] status; delete[] login; delete[] password;
//	fin.close();
//}
//
//void ExecutionProc::AddAcc(const char* status, Connection& connect)
//{
//	cout << "Add Accounts" << status << ">" << endl;
//
//	char* surname = new char[100]; char* name = new char[100];
//	char* patronymic = new char[100]; char* login = new char[100];
//	char* password = new char[100];
//
//	connect.SendStr(status);
//
//	serv.setLine(surname, connect);
//	serv.setLine(name, connect);
//	serv.setLine(patronymic, connect);
//
//	setLogin(login, connect);
//
//	serv.setLine(password, connect);
//	User obj(surname, name, patronymic, status, login, password);
//	this->vectUser.push_back(obj);
//
//	delete[] surname; delete[] name; delete[] patronymic;
//	delete[] login; delete[] password;
//}
//
//void ExecutionProc::setLogin(char*& login, Connection& connect)
//{
//	int k;
//	char* buf = new char[100];
//	char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm._-1234567890";
//	do {
//		k = 0;
//		serv.setLine(buf, connect);
//		if (strlen(buf) < 6)
//		{
//			k = 1;
//		}
//		else
//		{
//			for (register int i = 0; buf[i] != '\0'; i++)
//			{
//				k = 2;
//				for (register int j = 0; symbols[j] != '\0'; j++)
//				{
//					if (buf[i] == symbols[j])
//					{
//						k = 0;
//						break;
//					}
//				}
//				if (k == 2)
//					break;
//			}
//			if (k == 0)
//			{
//				for (vector<User>::iterator it = vectUser.begin(); it != vectUser.end(); it++)
//				{
//					if (strcmp(it->getLogin(), buf) == 0)
//					{
//						k = 3;
//						break;
//					}
//				}
//			}
//		}
//		connect.SendInt(k);
//	} while (k != 0);
//	strcpy(login, buf);
//	delete[] buf;
//}
//
//void ExecutionProc::OutputAcc(Connection& connect)
//{
//	cout << "Output Accounts" << endl;
//	connect.SendInt(vectUser.size());
//	for (vector<User>::iterator it = this->vectUser.begin(); it != this->vectUser.end(); it++)
//	{
//		connect.SendStr(it->getStatus());
//		connect.SendStr(it->getLogin());
//
//		connect.SendStr(UserStatus);
//		if (strcmp(UserStatus, "MAIN") == 0)
//			connect.SendStr(it->getPassword());
//
//		connect.SendStr(it->getSurname());
//		connect.SendStr(it->getName());
//		connect.SendStr(it->getPatronymic());
//	}
//}
//
//void ExecutionProc::DeleteAcc(Connection& connect)
//{
//	cout << "Deleting Accounts" << endl;
//	int choice;
//	do {
//		OutputAcc(connect);
//		choice = serv.Datacheck(0, vectUser.size(), connect);
//		if (choice != 0)
//		{
//			if (strcmp(vectUser[choice - 1].getLogin(), UserLogin) == 0)
//			{
//				connect.SendInt(1);
//			}
//			else if (strcmp(UserStatus, "ADMIN") == 0 && (strcmp(vectUser[choice - 1].getStatus(), "ADMIN") == 0 || strcmp(vectUser[choice - 1].getStatus(), "MAIN") == 0))
//			{
//				connect.SendInt(2);
//			}
//			else
//			{
//				connect.SendInt(3);
//				int del = serv.Datacheck(1, 2, connect);
//				if (del == 1)
//				{
//					if (vectReview.size() > 0 && strcmp(vectUser[choice - 1].getStatus(), "EXPERT") == 0)
//					{
//						for (int i = 0; i < vectReview.size(); i++)
//						{
//							if (strcmp(vectReview[i].getLog(), vectUser[choice - 1].getLogin()) == 0)
//								vectReview.erase(vectReview.cbegin() + i);
//						}
//					}
//					this->vectUser.erase(vectUser.cbegin() + (choice - 1));
//
//				}
//			}
//		}
//	} while (choice != 0);
//}
//
//void ExecutionProc::WriteAcc()
//{
//	cout << "Write Accounts" << endl;
//	ofstream fout("Users.txt", ios_base::trunc);
//	char* login = new char[100];
//	char* password = new char[100];
//	for (vector<User>::iterator it = this->vectUser.begin(); it != this->vectUser.end(); it++)
//	{
//		strcpy(login, it->getLogin());
//		for (int i = 0; login[i] != '\0'; i++)
//			login[i] -= 5;
//		strcpy(password, it->getPassword());
//		for (int j = 0; password[j] != '\0'; j++)
//			password[j] -= 10;
//		fout << it->getStatus() << " " << login << " " << password << " "
//			<< it->getSurname() << " " << it->getName() << " " << it->getPatronymic() << endl;
//	}
//	delete[] login;
//	delete[] password;
//	fout.close();
//}
//
//int ExecutionProc::Authorization(Connection& connect)
//{
//	cout << "Authorization" << endl;
//	int result = 0;
//	char* login = new char[100];
//	char* password = new char[100];
//	while (1)
//	{
//		serv.setLine(login, connect);
//		serv.setLine(password, connect);
//		for (int i = 0; i < vectUser.size(); i++)
//		{
//			if (strcmp(login, vectUser[i].getLogin()) == 0 && strcmp(password, vectUser[i].getPassword()) == 0)
//			{
//				serv.copyLine(UserStatus, vectUser[i].getStatus());
//				serv.copyLine(UserLogin, vectUser[i].getLogin());
//				if (strcmp(vectUser[i].getStatus(), "ADMIN") == 0 || strcmp(vectUser[i].getStatus(), "MAIN") == 0)
//				{
//					result = 1;
//					break;
//				}
//				else if (strcmp(vectUser[i].getStatus(), "EXPERT") == 0)
//				{
//					result = 2;
//					break;
//				}
//				else { result = 3; break; }
//			}
//		}
//		connect.SendInt(result);
//		if (result == 0)
//		{
//			if (serv.Datacheck(1, 2, connect) == 2)
//				break;
//		}
//		else break;
//	}
//	delete[] login;
//	delete[] password;
//	return result;
//}



void ExecutionProc::Read()
{
	cout << "Reading Prod" << endl;
	ifstream fin("Prod.txt", ios_base::in);
	char* info = new char[256]; char* type = new char[100];
    char* demand = new char[100];
	double sum; int quantity; double expectation; double incom;
	while (fin >> info >> type >> demand >> sum >> quantity >> expectation >> incom)
	{
		ProductRange obj(info, type, demand, sum, quantity, expectation, incom);
		this->vectProd.push_back(obj);
	}
	delete[] info; delete[] type; delete[] demand;
	fin.close();
}

void ExecutionProc::Write()
{
	cout << "Write Prod" << endl;
	if (this->vectProd.size() > 0)
	{
		ofstream fout("Prod.txt", ios_base::trunc);
		for (vector<ProductRange>::iterator it = vectProd.begin(); it != vectProd.end(); it++)
		{
			fout << it->getInfo() << " " << it->getType() << " " <<
				it->getDemand() << " " << it->getSum() << " " << it->getQuantity() << " " <<
				it->getExpectation() << " " << it->getIncom() << endl;
		}
		fout.close();
	}
}

void ExecutionProc::Add(Connection& connect)
{
		cout << "Add Prod" << endl;

		int choice = 0, a, b;

		connect.SendInt(vectReview.size());
		if (vectReview.size() > 0)
		{
			choice = serv.Datacheck(1, 2, connect);
			try {
				if (choice == 1)
				{
					throw 1;
				}
			}
			catch (int) {
				this->vectReview.clear();
				ofstream fout("Review.txt", ios_base::trunc);
				fout.close();
			}
		}
			
		if (choice != 2)
		{
			char* info = new char[256]; char* type = new char[100];
	       	char* demand = new char[100];
			double sum; int quantity; double expectation; double incom;

			setType(type, connect);
			serv.setLine(info, connect);
			setDemand(demand, connect);

			sum = serv.Datacheck(1.0, 100000.0, connect);
			quantity = serv.Datacheck(1, 1200, connect);
			expectation = serv.Datacheck(0.00, 10000.00, connect);
			incom = (sum * quantity) - expectation;

			ProductRange obj(info, type, demand, sum, quantity, expectation, incom);
			this->vectProd.push_back(obj);

			delete[] info; delete[] type; delete[] demand;
		}
				
}

void ExecutionProc::setType(char*& type, Connection& connect)
{
	int choice;
	choice = serv.Datacheck(1, 3, connect);
	switch (choice)
	{
	case 1:
		strcpy(type, "Овощи");
		break;
	case 2:
		strcpy(type, "Фрукты");
		break;
	case 3:
		strcpy(type, "Мясо");
		break;
	default:
		strcpy(type, "-");
		break;
	}
}

void ExecutionProc::setDemand(char*& currency, Connection& connect)
{
	int a, b;
	int choice = serv.Datacheck(1, 3, connect);
	switch (choice)
	{
	case 1:
		strcpy(currency, "Высокий");
		break;
	case 2:
		strcpy(currency, "Средний");
		break;
	case 3:
		strcpy(currency, "Низкий");
		break;
	default:
		strcpy(currency, "-");
		break;
	}
}

void ExecutionProc::OutPut(Connection& connect)
{
	cout << "OutputProd" << endl;
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		for (vector<ProductRange>::iterator it = vectProd.begin(); it != vectProd.end(); it++)
		{
			connect.SendStr(it->getType());
			connect.SendStr(it->getInfo());
			connect.SendStr(it->getDemand());
			connect.SendDouble(it->getSum());
			connect.SendInt(it->getQuantity());
			connect.SendDouble(it->getExpectation());
			connect.SendDouble(it->getIncom());
		}
	}
}

void ExecutionProc::OutputProdUser(Connection& connect) {
	cout << "OutputProd" << endl;
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		for (vector<ProductRange>::iterator it = vectProd.begin(); it != vectProd.end(); it++)
		{
			connect.SendStr(it->getType());
			connect.SendStr(it->getInfo());
			connect.SendInt(it->getQuantity());
		}
	}
}

void ExecutionProc::EditProd(Connection& connect)
{
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		int choice;
		do {
			OutPut(connect);
			choice = serv.Datacheck(0, vectProd.size(), connect);
			if (choice != 0)
			{
				char* str = new char[100]; double sum; double expectation; int quantity;
				ProductRange obj(this->vectProd[choice - 1]);
				int edit = serv.Datacheck(0, 4, connect);
				switch (edit)
				{
				case 1:
					setType(str, connect);
					obj.setType(str);
					break;
				case 2:
					serv.setLine(str, connect);
					obj.setInfo(str);
					break;
				case 3:
					setDemand(str, connect);
					obj.setDemand(str);
					break;
				case 4:
					sum = serv.Datacheck(1.0, 100000.0, connect);
					quantity = serv.Datacheck(1, 1200, connect);
					expectation = serv.Datacheck(0.00, 100000.00, connect);
					obj.setIncom(sum, quantity, expectation);
					break;
				}
				vectProd[choice - 1] = obj;
				delete[] str;
			}
		} while (choice != 0);
	}
}

void ExecutionProc::DeleteProd(Connection& connect)
{
	int choice = 0;

	connect.SendInt(vectReview.size());
	if (vectReview.size() > 0)
	{
		choice = serv.Datacheck(1, 2, connect);
		if (choice == 1)
		{
			vectReview.clear();
			ofstream fout("Review.txt", ios_base::trunc);
			fout.close();
		}
	}
	if (choice != 2)
	{
		connect.SendInt(vectProd.size());
		if (vectProd.size() > 0)
		{
			do {
				OutPut(connect);
				choice = serv.Datacheck(0, vectProd.size(), connect);
				if (choice != 0)
				{
					int del = serv.Datacheck(1, 2, connect);
					if (del == 1)
					{
						vectProd.erase(vectProd.cbegin() + choice - 1);
					}
				}
			} while (choice != 0);
		}
	}
}

void ExecutionProc::SeaFiltrProd(Connection& connect)
{
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		char* info = new char[256]; char* type = new char[100];
		char* demand = new char[100];
		int minI = 0, maxI = 0;
		double minD = 0, maxD = 0;
		int choice = serv.Datacheck(1, 6, connect);
		switch (choice)
		{
		case 1:
			setType(type, connect);
			break;
		case 2:
			serv.setLine(info, connect);
			break;
		case 3:
			setDemand(demand, connect);
			break;
		case 4:
			minD = serv.Datacheck(0.00, 100.00, connect);
			maxD = serv.Datacheck(minD, 100.00, connect);
			break;
		case 5:
			minI = serv.Datacheck(0, 1200, connect);
			maxI = serv.Datacheck(minI, 1200, connect);
			break;
		case 6:
			minD = serv.Datacheck(0.00, 100000.00, connect);
			maxD = serv.Datacheck(minD, 100000.00, connect);
			break;

		}
		connect.SendInt(vectProd.size());
		for (vector<ProductRange>::iterator it = vectProd.begin(); it != vectProd.end(); it++)
		{
			int k = 0;
			switch (choice)
			{
			case 1:
				if (strcmp(it->getType(), type) == 0) k = 1;
				break;
			case 2:
				if (strcmp(it->getInfo(), info) == 0) k = 1;
				break;
			case 3:
				if (strcmp(it->getDemand(), demand) == 0) k = 1;
				break;
			case 4:
				if (it->getSum() >= minD && it->getSum() <= maxD) k = 1;
				break;
			case 5:
				if (it->getQuantity() >= minI && it->getQuantity() <= maxI) k = 1;
				break;
			case 6:
				if (it->getExpectation() >= minD && it->getExpectation() <= maxD) k = 1;
				break;
			}
			connect.SendInt(k);
			if (k == 1)
			{
				connect.SendStr(it->getType());
				connect.SendStr(it->getInfo());
				connect.SendStr(it->getDemand());
				connect.SendDouble(it->getSum());
				connect.SendInt(it->getQuantity());
				connect.SendDouble(it->getExpectation());
				connect.SendDouble(it->getIncom());
			}
		}
		delete[] info; delete[] type; delete[] demand;
	}
}

void ExecutionProc::SeaFiltrProdUser(Connection& connect)
{
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		char* info = new char[256]; char* type = new char[100];
		double minD = 0, maxD = 0, d;
		int choice = serv.Datacheck(1, 6, connect);
		switch (choice)
		{
		case 1:
			setType(type, connect);
			break;
		case 2:
			serv.setLine(info, connect);
			break;
		case 3:
			minD = serv.Datacheck(0.00, 100.00, connect);
			maxD = serv.Datacheck(minD, 100.00, connect);
			break;
		}
		connect.SendInt(vectProd.size());
		for (vector<ProductRange>::iterator it = vectProd.begin(); it != vectProd.end(); it++)
		{
			int k = 0;
			switch (choice)
			{
			case 1:
				if (strcmp(it->getType(), type) == 0) k = 1;
				break;
			case 2:
				if (strcmp(it->getInfo(), info) == 0) k = 1;
				break;
			case 3:
				if (it->getSum() >= minD && it->getSum() <= maxD) k = 1;
				break;
			}
			connect.SendInt(k);
			if (k == 1)
			{
				connect.SendStr(it->getType());
				connect.SendStr(it->getInfo());
				connect.SendDouble(it->getSum());
			}
		}
		delete[] info; delete[] type;
	}
}

void ExecutionProc::ReadReview()
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
			vectReview.push_back(obj);

		}
		delete[] opinion;
	}
	delete[] log;
	fin.close();
}

void ExecutionProc::WriteReview()
{
	cout << "Write Review" << endl;
	if (this->vectReview.size() > 0)
	{
		ofstream fout("Review.txt", ios_base::trunc);
		for (vector<Review>::iterator it = vectReview.begin(); it != vectReview.end(); it++)
		{
			fout << it->getLog() << " " << it->getCounter();;
			for (int i = 0; i < it->getCounter(); i++)
				fout << " " << it->getReview()[i];
			fout << endl;
		}
		fout.close();
	}
}

void ExecutionProc::AddReview(Connection& connect)
{
	connect.SendInt(vectProd.size());
	if (vectProd.size() > 0)
	{
		int* opinion = new int[vectProd.size()];
		int k = 0;
		OutPut(connect);
		for (int i = 0; i < vectProd.size(); i++)
		{
			do {
				k = 0;
				opinion[i] = serv.Datacheck(1, vectProd.size(), connect);
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (opinion[i] == opinion[j] && i != j)
					{
						k = 1;
						break;
					}
				}
				connect.SendInt(k);
			} while (k != 0);
		}
		Review obj(UserLogin, opinion, vectProd.size());
		if (vectReview.size() > 0)
		{
			for (int i = 0; i < vectReview.size(); i++)
			{
				if (strcmp(vectReview[i].getLog(), UserLogin) == 0)
				{
					vectReview[i] = obj;
					k = 1;
					break;
				}
			}
		}
		if (k == 0)
		{

			vectReview.push_back(obj);
		}
		delete[] opinion;
	}
}

void ExecutionProc::OutputReview(Connection& connect)
{
	connect.SendInt(vectReview.size());
	if (vectReview.size() > 0)
	{
		int k = -1;

		for (int i = 0; i < vectReview.size(); i++)
		{
			if (strcmp(vectReview[i].getLog(), UserLogin) == 0)
			{
				k = i;
				break;
			}
		}
		connect.SendInt(k);

		if (k != -1)
		{
			int** exp_arr = new int* [vectProd.size()];
			for (int j = 0; j < vectProd.size(); j++)
				exp_arr[j] = new int[vectProd.size()];

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (i == j)
						exp_arr[i][j] = -1;
					else exp_arr[i][j] = -2;
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					int z = vectReview[k].getReview()[i];
					if (exp_arr[z - 1][j] == -2)
					{
						exp_arr[z - 1][j] = 1;
					}
					if (exp_arr[j][z - 1] == -2)
					{
						exp_arr[j][z - 1] = 0;
					}
				}
			}
			OutPut(connect);
			connect.SendInt(vectProd.size());
			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					connect.SendInt(exp_arr[i][j]);
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
				delete[] exp_arr[i];
			delete[] exp_arr;
			connect.SendInt(vectReview[k].getReview()[0]);
		}
	}

}

void ExecutionProc::Kondorse(Connection& connect)
{
	connect.SendInt(vectReview.size());
	if (vectReview.size() > 0)
	{
		int** main_arr = new int* [vectProd.size()];
		for (int j = 0; j < vectProd.size(); j++)
			main_arr[j] = new int[vectProd.size()];

		int** exp_arr = new int* [vectProd.size()];
		for (int j = 0; j < vectProd.size(); j++)
			exp_arr[j] = new int[vectProd.size()];

		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				if (i == j)
					main_arr[i][j] = -1;
				else main_arr[i][j] = 0;
			}
		}

		for (int opin = 0; opin < vectReview.size(); opin++)
		{

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (i == j)
						exp_arr[i][j] = -1;
					else exp_arr[i][j] = -2;
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					int z = vectReview[opin].getReview()[i];
					if (exp_arr[z - 1][j] == -2)
					{
						exp_arr[z - 1][j] = 1;
					}
					if (exp_arr[j][z - 1] == -2)
					{
						exp_arr[j][z - 1] = 0;
					}
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (i != j)
						main_arr[i][j] += exp_arr[i][j];
				}
			}

		}

		OutPut(connect);
		connect.SendInt(vectProd.size());
		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				connect.SendInt(main_arr[i][j]);
			}
		}

		int* finding = new int[vectProd.size()];
		for (int i = 0; i < vectProd.size(); i++)
			finding[i] = 0;

		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				if (i != j)
				{
					if (main_arr[i][j] >= main_arr[j][i])
					{
						finding[i] += 1;
					}
				}
			}
		}

		int max = 0;
		for (int i = 0; i < vectProd.size(); i++)
		{
			if (finding[max] < finding[i])
			{
				max = i;
			}
		}

		connect.SendInt(max + 1);

		delete[] finding;

		for (int i = 0; i < vectProd.size(); i++)
		{
			delete[] exp_arr[i];
			delete[] main_arr[i];
		}
		delete[] exp_arr;
		delete[] main_arr;
	}
}

void ExecutionProc::KondorseUser(Connection& connect)
{
	connect.SendInt(vectReview.size());
	if (vectReview.size() > 0)
	{
		int** main_arr = new int* [vectProd.size()];
		for (int j = 0; j < vectProd.size(); j++)
			main_arr[j] = new int[vectProd.size()];

		int** exp_arr = new int* [vectProd.size()];
		for (int j = 0; j < vectProd.size(); j++)
			exp_arr[j] = new int[vectProd.size()];

		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				if (i == j)
					main_arr[i][j] = -1;
				else main_arr[i][j] = 0;
			}
		}

		for (int opin = 0; opin < vectReview.size(); opin++)
		{

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (i == j)
						exp_arr[i][j] = -1;
					else exp_arr[i][j] = -2;
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					int z = vectReview[opin].getReview()[i];
					if (exp_arr[z - 1][j] == -2)
					{
						exp_arr[z - 1][j] = 1;
					}
					if (exp_arr[j][z - 1] == -2)
					{
						exp_arr[j][z - 1] = 0;
					}
				}
			}

			for (int i = 0; i < vectProd.size(); i++)
			{
				for (int j = 0; j < vectProd.size(); j++)
				{
					if (i != j)
						main_arr[i][j] += exp_arr[i][j];
				}
			}

		}

		OutputProdUser(connect);
		connect.SendInt(vectProd.size());
		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				connect.SendInt(main_arr[i][j]);
			}
		}

		int* finding = new int[vectProd.size()];
		for (int i = 0; i < vectProd.size(); i++)
			finding[i] = 0;

		for (int i = 0; i < vectProd.size(); i++)
		{
			for (int j = 0; j < vectProd.size(); j++)
			{
				if (i != j)
				{
					if (main_arr[i][j] >= main_arr[j][i])
					{
						finding[i] += 1;
					}
				}
			}
		}

		int max = 0;
		for (int i = 0; i < vectProd.size(); i++)
		{
			if (finding[max] < finding[i])
			{
				max = i;
			}
		}

		connect.SendInt(max + 1);

		delete[] finding;

		for (int i = 0; i < vectProd.size(); i++)
		{
			delete[] exp_arr[i];
			delete[] main_arr[i];
		}
		delete[] exp_arr;
		delete[] main_arr;
	}
}

ExecutionProc::~ExecutionProc()
{
	delete[] UserStatus;
	delete[] UserLogin;
	//if (this->vectUser.size() > 0)
	//	vectUser.clear();
	if (this->vectProd.size() > 0)
		vectProd.clear();
	if (this->vectReview.size() > 0)
		vectReview.clear();
	/*cout << "Деструк Interaction" << endl;*/
}
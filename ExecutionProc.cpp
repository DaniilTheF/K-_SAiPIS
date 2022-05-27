#include "ExecutionProc.h"

void ExecutionProc::AddAcc(Connection& connect)
{
	char* buf = new char[100];
	connect.RecvStr(buf);
	cout << "\t����������� <" << buf << ">" << endl;
	cout << "�������: "; klient.setStr(connect);
	cout << "���: "; klient.setStr(connect);
	cout << "��������: "; klient.setStr(connect);
	cout << "Login: "; setLogin(connect);
	cout << "Password: "; klient.setStr(connect);
	delete[] buf;
}

void ExecutionProc::setLogin(Connection& connect)
{
	int k;
	do {
		klient.setStr(connect);
		k = connect.RecvInt();
		if (k == 1)
			cout << "Login ������ ��������� 6 ��� ����� ��������" << endl;
		else if (k == 2)
			cout << "Login ����� ��������� ��������� �����, ����� � ����������� �������(-._)" << endl;
		else if (k == 3)
			cout << "������ Login ����� ������ �������������" << endl;
		if (k != 0)
			cout << "������� Login: ";
	} while (k != 0);
}

void ExecutionProc::OutPutAcc(Connection& connect)
{
	char* buf = new char[100];
	int n = connect.RecvInt();
	klient.setLine(111, '='); cout << endl;
	cout << "|" << setw(5) << "  #" << "|" << setw(15) << "Status" << "|" << setw(20) << "Login" << "|"
		<< setw(20) << "Password" << "|" << setw(45) << "���" << "|" << endl;
	klient.setLine(111, '='); cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "|" << setw(5) << i + 1;
		connect.RecvStr(buf); cout << "|" << setw(15) << buf;
		connect.RecvStr(buf); cout << "|" << setw(20) << buf;

		connect.RecvStr(buf);
		if (strcmp(buf, "MAIN") == 0)
		{
			connect.RecvStr(buf); cout << "|" << setw(20) << buf;
		}
		else { cout << "|" << setw(20) << "����������"; }
		connect.RecvStr(buf); cout << "|" << setw(15) << buf;
		connect.RecvStr(buf); cout << setw(15) << buf;
		connect.RecvStr(buf); cout << setw(15) << buf << "|" << endl;
		klient.setLine(111, '-'); cout << endl;
	}
	delete[] buf;
}

void ExecutionProc::DeleteAcc(Connection& connect)
{
	int choice;
	do {
		system("cls");
		OutPutAcc(connect);
		cout << "����� ������, ������� ������ �������(0 - ��������� �����): ";
		choice = klient.checkDatai(connect);
		if (choice != 0)
		{
			choice = connect.RecvInt();
			if (choice == 1)
			{
				cout << "������ ������� ����������� ������� ������" << endl;
				Sleep(2000);
			}
			else if (choice == 2)
			{
				cout << "" << endl;
				Sleep(2000);
			}
			else
			{
				cout << "�� ������������� ��������? (1 - �� / 2 - ���):";
				klient.checkDatai(connect);
			}
		}
	} while (choice != 0);
}

int ExecutionProc::Authorization(Connection& connect)
{
	int result;
	while (1)
	{
		system("cls");
		cout << "\tLogin: "; klient.setStr(connect);
		cout << "\tPassword: "; klient.encription(connect);
		result = connect.RecvInt();
		if (result == 0)
		{
			cout << "������������ ����� ��� ������!" << endl;
			cout << "��� ���������� ����� ������ ������� 1 ��� ��� ������ ������� 2:" << endl;
			if (klient.checkDatai(connect) == 2)
				break;
		}
		else break;
	}
	return result;
}



void ExecutionProc::AddProd(Connection& connect)
{
	int choice = 0;

	if (connect.RecvInt() > 0)
	{
		cout << "��� ����������  ������������ �������� ��������� ����� ������� ������������ ���������" << endl;
		cout << "1. �������� �������" << endl;
		cout<< "2. �� ��������� �������" << endl;
		cout << "��� �����: ";
		choice = klient.checkDatai(connect);
	}
	if (choice != 2)
	{
		setType(connect); // ��� ���������� ���� ��������
		cout << "�������� � ���� ��������: ";
		klient.setStr(connect);
		setDemand(connect); // ��� ���������� ������ ���������
		cout << "��������� �������� ��� ������� (���. �������� ��.): ";
		klient.checkDatad(connect);
		cout << "��������� ���-�� ��������� ���������: ";
		klient.checkDatai(connect);
		cout << "������� �� ��������� ���������: ";
		klient.checkDatad(connect);;
	}
}

void ExecutionProc::setType(Connection& connect)
{
	cout << "\t���� ���������" << endl;
	cout << "1 - �����" << endl;
	cout << "2 - ������" << endl;
	cout << "3 - ����" << endl;
	cout << "��� �����: ";  klient.checkDatai(connect);
}

void ExecutionProc::setDemand(Connection& connect)
{
	cout << "\t����� �� ��������� �� �����" << endl;
	cout << "1 - �������" << endl;
	cout << "2 - �������" << endl;
	cout << "3 - ������" << endl;
	cout << "��� �����: "; klient.checkDatai(connect);
}
				
void ExecutionProc::OutputProd()
{
	klient.setLine(207, '='); cout << endl;
	cout << "|" << setw(3) << "#  " << "|" << setw(10) << "��� ����. " << "|"
		<< setw(25) << "������� ���������� � ����. " << "|" << setw(32)
		<< " ����� �� ����. �� ����� " << "|" << setw(23) << " ��������� ����. ��� �������: " << "|" << setw(25)
		<< " ��������� ���-�� ��������� ����.: " << "|" << setw(15) << " ������� �� ��������� ����. " << "|" << setw(30) << " ��������� ����� � ��������� ����." << "|" << endl;
	klient.setLine(207, '='); cout << endl;
}

void ExecutionProc::OutputAllProd(Connection& connect)
{
	char* str1 = new char[100];
	int n = connect.RecvInt();
	if (n > 0)
	{
		OutputProd();
		for (int i = 0; i < n; i++)
		{
			cout << "|" << setw(3) << i + 1;
			connect.RecvStr(str1); cout << "|" << setw(10) << str1;
			connect.RecvStr(str1); cout << "|" << setw(26) << str1;
			connect.RecvStr(str1); cout << "|" << setw(33) << str1;
			cout << "|" << setw(30) << connect.RecvDouble();
			cout << "|" << setw(35) << connect.RecvInt();
			cout << "|" << setw(28) << connect.RecvDouble();
			cout << "|" << setw(34) << connect.RecvDouble() << "|" << endl;
			klient.setLine(207, '-'); cout << endl;
		}
	}
	else { cout << "��� �������" << endl; Sleep(1500); }
	delete[] str1;
}

void ExecutionProc::OutputProdUser(Connection& connect) {
	char* str1 = new char[100];
	int n = connect.RecvInt();
	if (n > 0)
	{

		klient.setLine(207, '='); cout << endl;
		cout << "|" << setw(3) << "#  " << "|" << setw(10) << "��� ������� " << "|"
			<< setw(26) << "������� ���������� � �������� "
			"|" << setw(19) << " ��������� ���������:  " << "|" << endl;
		klient.setLine(207, '='); cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "|" << setw(3) << i + 1;
			connect.RecvStr(str1); cout << "|" << setw(12) << str1;
			connect.RecvStr(str1); cout << "|" << setw(30) << str1;
			cout << "|" << setw(23) << connect.RecvInt() << "|" << endl;
			klient.setLine(207, '-'); cout << endl;
		}
	}
	else { cout << "��� �������" << endl; Sleep(1500); }
	delete[] str1;
}

void ExecutionProc::EditProd(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		int choice;
		do {
			system("cls");
			OutputAllProd(connect);
			cout << "����� ������, ������� ������ ��������(0 - ��������� �����): ";
			choice = klient.checkDatai(connect);
			if (choice != 0)
			{
				cout << "\t�������� ��������������" << endl;
				cout << "1 - ��� ���������" << endl;
				cout << "2 - ����� ��������" << endl;
				cout << "3 - ����� �� ��������� �� ����� " << endl;
				cout << "4 - ������ �������� �� �����" << endl;
				cout << "��� �����: "; int edit = klient.checkDatai(connect);
				switch (edit)
				{
				case 1:
					cout << "��� ���������: ";
					setType(connect);
					break;
				case 2:
					klient.setStr(connect);
					break;
				case 3:
					cout << "����� ��������� �� �����: ";
					setDemand(connect);
					break;
				case 4:
					cout << " ��������� �������� ��� �������(���.�������� ��.) :";
					klient.checkDatad(connect);
					cout << "��������� ���-�� ��������� ���������: ";
					klient.checkDatai(connect);
					cout << "������� �� ��������� ���������: ";
					klient.checkDatad(connect);
					break;
				}
			}
		} while (choice != 0);
	}
	else
	{
		cout << "��� �������" << endl;
		Sleep(1500);
	}
}

void ExecutionProc::DeleteProd(Connection& connect)
{
	int choice = 0;

	if (connect.RecvInt() > 0)
	{
		cout << "��������������!" << endl;
		cout << "��� �������� ������������ �������� ��������� ����� ������� ������������ ���������" << endl;
		cout << "1. ������� �������" << endl;
		cout << "2. �� ������� �������" << endl;
		cout << "��� �����: "; choice = klient.checkDatai(connect);
	}
	if (choice != 2)
	{
		if (connect.RecvInt() > 0)
		{
			do {
				system("cls");
				OutputAllProd(connect);
				cout << "����� ������, ������� ������ �������(0 - ��������� �����): ";
				choice = klient.checkDatai(connect);
				if (choice != 0)
				{
					cout << "�� ������������� ��������? 1 - �� | 2 - ���:";
					int del = klient.checkDatai(connect);
				}
			} while (choice != 0);
		}
		else
		{
			cout << "��� �������" << endl;
			Sleep(1500);
		}
	}
}

void ExecutionProc::SeaFiltrProd(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		cout << "\t����� � ����������" << endl;
		cout << "1 - ����� �� ���� ���������" << endl;
		cout << "2 - ����� �� ����� ��������" << endl;
		cout << "3 - ����� �� ������ �� �����" << endl;
		cout << "4 - ���������� �� ��������� ��������" << endl;
		cout << "5 - ���������� �� ���������� ���������� ��������" << endl;
		cout << "6 - ���������� �� �������� �� ���������" << endl;
		cout << "��� �����: "; int choice = klient.checkDatai(connect);
		switch (choice)
		{
		case 1:
			setType(connect);
			break;
		case 2:
			cout << "����� ��������: ";
			klient.setStr(connect);
			break;
		case 3:
			setDemand(connect);
			break;
		case 4:
			cout << "Min: ";
			klient.checkDatad(connect);
			cout << "Max: ";
			klient.checkDatad(connect);
			break;
		case 5:
			cout << "Min: ";
			klient.checkDatai(connect);
			cout << "Max: ";
			klient.checkDatai(connect);
			break;
		case 6:
			cout << "Min: ";
			klient.checkDatad(connect);
			cout << "Max: ";
			klient.checkDatad(connect);
			break;
		}
		int counter = connect.RecvInt();
		char* str1 = new char[100];
		OutputProd();
		for (int i = 0; i < counter; i++)
		{
			if (connect.RecvInt() == 1)
			{
				cout << "|" << setw(3) << i + 1;
				connect.RecvStr(str1); cout << "|" << setw(10) << str1;
				connect.RecvStr(str1); cout << "|" << setw(26) << str1;
				connect.RecvStr(str1); cout << "|" << setw(33) << str1;
				cout << "|" << setw(30) << connect.RecvDouble();
				cout << "|" << setw(35) << connect.RecvInt();
				cout << "|" << setw(28) << connect.RecvDouble();
				cout << "|" << setw(34) << connect.RecvDouble() << "|" << endl;
				klient.setLine(207, '-'); cout << endl;
			}
		}
		delete[] str1;
		system("pause");
	}
	else
	{
		cout << "��� �������" << endl;
		Sleep(1500);
	}
}

void ExecutionProc::SeaFiltrProdUser(Connection& connect) {
	if (connect.RecvInt() > 0)
	{
		cout << "\t����� � ����������" << endl;
		cout << "1 - ����� �� ���� ���������" << endl;
		cout << "2 - ����� �� ����� ��������" << endl;
		cout << "3 - ���������� �� ��������� ��������" << endl;
		cout << "��� �����: "; int choice = klient.checkDatai(connect);
		switch (choice)
		{
		case 1:
			setType(connect);
			break;
		case 2:
			cout << "����� ��������: ";
			klient.setStr(connect);
			break;
		case 3:
			cout << "Min: ";
			klient.checkDatad(connect);
			cout << "Max: ";
			klient.checkDatad(connect);
			break;
		}
		int counter = connect.RecvInt();
		char* str1 = new char[100];
		klient.setLine(207, '='); cout << endl;
		cout << "|" << setw(3) << "#  " << "|" << setw(10) << "��� ������� " << "|"
			<< setw(26) << "������� ���������� � �������� "
			"|" << setw(19) << " ��������� ���������:  " << "|" << endl;
		klient.setLine(207, '='); cout << endl;
		for (int i = 0; i < counter; i++)
		{
			if (connect.RecvInt() == 1)
			{
				cout << "|" << setw(3) << i + 1;
				connect.RecvStr(str1); cout << "|" << setw(10) << str1;
				connect.RecvStr(str1); cout << "|" << setw(26) << str1;
				cout << "|" << setw(30) << connect.RecvDouble() << endl;
				klient.setLine(207, '-'); cout << endl;
			}
		}
		delete[] str1;
		system("pause");
	}
	else
	{
		cout << "��� �������" << endl;
		Sleep(1500);
	}
}


void ExecutionProc::AddReview(Connection& connect)
{
	int counter = connect.RecvInt();
	if (counter > 0)
	{
		int k;
		OutputAllProd(connect);
		cout << "\t\t\t������������ �����������" << endl;
		for (int i = 0; i < counter; i++)
		{
			do {
				k = 0;
				cout << i + 1 << ") �����(������������): ";
				klient.checkDatai(connect);
				k = connect.RecvInt();
				if (k != 0)
				{
					cout << "������ ������������ ��� ������������!" << endl;
				}
			} while (k != 0);
		}
	}
	else { cout << "��� ������������ �������� ���������" << endl; Sleep(1500); }
}

void ExecutionProc::OutputReview(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		int k = -1;
		k = connect.RecvInt();
		if (k != -1)
		{
			OutputAllProd(connect);
			cout << "���� ������ Aij, ��������������� ������������ �����������:" << endl;
			int buf;
			int counter = connect.RecvInt();

			klient.setLine((11 * counter) + 6, '-'); cout << endl;
			cout << setw(5) << "Aij";
			for (int i = 0; i < counter; i++)
				cout << "|" << setw(7) << "A[" << setw(2) << i + 1 << "]";
			cout << "|" << endl;
			klient.setLine((11 * counter) + 6, '-'); cout << endl;

			for (int i = 0; i < counter; i++)
			{
				cout << "A[" << setw(2) << i + 1 << "]";
				for (int j = 0; j < counter; j++)
				{
					buf = connect.RecvInt();
					if (buf == -1)
						cout << "|" << setw(10) << "*****";
					else cout << "|" << setw(10) << buf;

				}
				cout << "|" << endl;
				klient.setLine((11 * counter) + 6, '-'); cout << endl;
			}
			cout << "�� ��������, ��� ��������� ������������� �������� ��������� ��������: ";
			cout << "������: " << connect.RecvInt() << endl;
			system("pause");
		}
		else
		{
			cout << "�� �� ������������ ������������ ����������� " << endl;
			Sleep(3000);
		}
	}
	else
	{
		cout << "�� �� ������������ ������������ ����������� " << endl;
		cout << "���� ������������� ���� ��������� � ������ ������������� �������� ���������" << endl;
		Sleep(3000);
	}
}

void ExecutionProc::Kondorse(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		OutputAllProd(connect);
		int buf;
		int counter = connect.RecvInt();

		klient.setLine((11 * counter) + 6, '-'); cout << endl;
		cout << setw(5) << "Aij";
		for (int i = 0; i < counter; i++)
			cout << "|" << setw(7) << "A[" << setw(2) << i + 1 << "]";
		cout << "|" << endl;
		klient.setLine((11 * counter) + 6, '-'); cout << endl;

		for (int i = 0; i < counter; i++)
		{
			cout << "A[" << setw(2) << i + 1 << "]";
			for (int j = 0; j < counter; j++)
			{
				buf = connect.RecvInt();
				if (buf == -1)
					cout << "|" << setw(10) << "*****";
				else cout << "|" << setw(10) << buf;

			}
			cout << "|" << endl;
			klient.setLine((11 * counter) + 6, '-'); cout << endl;
		}

		cout << "�� ������ ��������� ��������� ������������� �� ������ ������������ �������� ��������� ��������: ";
		cout << "������: " << connect.RecvInt() << endl;
		system("pause");
	}
	else { cout << "�������� ��� �� ����������� ������������" << endl; Sleep(2000); }
}
void ExecutionProc::KondorseUser(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		OutputProdUser(connect);
		int buf;
		int counter = connect.RecvInt();

		klient.setLine((11 * counter) + 6, '-'); cout << endl;
		cout << setw(5) << "Aij";
		for (int i = 0; i < counter; i++)
			cout << "|" << setw(7) << "A[" << setw(2) << i + 1 << "]";
		cout << "|" << endl;
		klient.setLine((11 * counter) + 6, '-'); cout << endl;

		for (int i = 0; i < counter; i++)
		{
			cout << "A[" << setw(2) << i + 1 << "]";
			for (int j = 0; j < counter; j++)
			{
				buf = connect.RecvInt();
				if (buf == -1)
					cout << "|" << setw(10) << "#####";
				else cout << "|" << setw(10) << buf;

			}
			cout << "|" << endl;
			klient.setLine((11 * counter) + 6, '-'); cout << endl;
		}

		cout << "�� ������ ��������� ��������� ������������� �� ������ ������������ �������� ��������� ��������: ";
		cout << "������ #" << connect.RecvInt() << endl;
		system("pause");
	}
	else { cout << "�������� ��� �� ����������� ������������" << endl; Sleep(2000); }
}
#include "Menu.h"
#include "Connection.h"

void Menu::main_menu()
{
	cout << "\t������� ����" << endl;
	cout << "1 - ���� � �������" << endl;
	cout << "2 - �����������" << endl;
	cout << "3 - �����" << endl;
}

void Menu::admin_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\t���� ������" << endl;
	connect.RecvStr(buf);
	
	connect.RecvStr(buf);
	cout << "\t1 - �������� �����������" << endl;
	cout << "\t2 - ������������� �����������" << endl;
	cout << "\t3 - �������� ������������" << endl;
	cout << "\t4 - ������� �����������" << endl;
	cout << "\t5 - ����� � ���������� ������������" << endl;
	cout << "\t6 - ������� ��������" << endl;
	cout << "\t7 - ���������� ����������" << endl;
	cout << "\t8 - �����" << endl;
	delete[] buf;
}

void Menu::expert_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\t���� ��������" << endl;
	connect.RecvStr(buf);
	
	connect.RecvStr(buf);
	cout << "\t1 - �������� ������������" << endl;
	cout << "\t2 - ����� � ���������� ������������" << endl;
	cout << "\t3 - ������������ �����������" << endl;
	cout << "\t4 - �������� ����������� ����������" << endl;
	cout << "\t5 - �����" << endl;
	delete[] buf;
}

void Menu::user_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\t���� ������������" << endl;
	connect.RecvStr(buf);

	connect.RecvStr(buf);
	cout << "\t1 - �������� ������������" << endl;
	cout << "\t2 - ����� � ���������� ������������" << endl;
	cout << "\t3 - ������� ��������" << endl;
	cout << "\t4 - �����" << endl;
	delete[] buf;
}

void Menu::control_acc()
{
	cout << "\t���������� ���������" << endl;
	cout << "1 - �������� ��������" << endl;
	cout << "2 - �������� ��������������" << endl;
	cout << "3 - �������� ���� ���������" << endl;
	cout << "4 - �������� ��������" << endl;
	cout << "5 - ��������� �����" << endl;
}
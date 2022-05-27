#include "Menu.h"
#include "Connection.h"

void Menu::main_menu()
{
	cout << "\tГлавное Меню" << endl;
	cout << "1 - Вход в аккаунт" << endl;
	cout << "2 - Регистрация" << endl;
	cout << "3 - Выход" << endl;
}

void Menu::admin_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\tМеню Админа" << endl;
	connect.RecvStr(buf);
	
	connect.RecvStr(buf);
	cout << "\t1 - Добавить ассортимент" << endl;
	cout << "\t2 - Редактировать ассортимент" << endl;
	cout << "\t3 - Просмотр ассортимента" << endl;
	cout << "\t4 - Удалить ассортимент" << endl;
	cout << "\t5 - Поиск и фильтрация ассортимента" << endl;
	cout << "\t6 - Принцип Кондорсе" << endl;
	cout << "\t7 - Управление аккаунтами" << endl;
	cout << "\t8 - Выход" << endl;
	delete[] buf;
}

void Menu::expert_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\tМеню Эксперта" << endl;
	connect.RecvStr(buf);
	
	connect.RecvStr(buf);
	cout << "\t1 - Просмотр ассортимента" << endl;
	cout << "\t2 - Поиск и фильтрация ассортимента" << endl;
	cout << "\t3 - Ранжирование альтернатив" << endl;
	cout << "\t4 - Просмотр собственной ранжировки" << endl;
	cout << "\t5 - Выход" << endl;
	delete[] buf;
}

void Menu::user_menu(Connection& connect)
{
	char* buf = new char[100];
	cout << "\t\t\tМеню Пользователя" << endl;
	connect.RecvStr(buf);

	connect.RecvStr(buf);
	cout << "\t1 - Просмотр ассортимента" << endl;
	cout << "\t2 - Поиск и фильтрация ассортимента" << endl;
	cout << "\t3 - Принцип Кондорсе" << endl;
	cout << "\t4 - Выход" << endl;
	delete[] buf;
}

void Menu::control_acc()
{
	cout << "\tУправление акаунтами" << endl;
	cout << "1 - Добавить Эксперта" << endl;
	cout << "2 - Добавить Администратора" << endl;
	cout << "3 - Просмотр всех аккаунтов" << endl;
	cout << "4 - Удаление аккаунта" << endl;
	cout << "5 - Вернуться назад" << endl;
}
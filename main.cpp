#include "Connection.h"
#include "ExecutionProc.h"
#include "CheckNumb.h"
#include "Menu.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	ExecutionProc inter;
	Connection connect;
	connect.conect();
	if (connect.RecvInt() == 0)
		inter.AddAcc(connect);
	Menu M;
	int choice, autho = 0;
	char* UserStatus = new char[100];
	while (1)
	{
		system("cls");
		M.main_menu();
		cout << "Ваш выбор: "; choice = klient.checkDatai(connect);
		switch (choice)
		{
		case 1:
			autho = inter.Authorization(connect);
			switch (autho)
			{
			case 1:
				while (1)
				{
					system("cls");
					M.admin_menu(connect);
					cout << "Ваш выбор: ";
					choice = klient.checkDatai(connect);
					switch (choice)
					{
					case 1:
						system("cls");
						inter.AddProd(connect);
						break;
					case 2:
						system("cls");
						inter.EditProd(connect);
						break;
					case 3:
						system("cls");
						inter.OutputAllProd(connect);
						system("pause");
						break;
					case 4:
						system("cls");
						inter.DeleteProd(connect);
						break;
					case 5:
						system("cls");
						inter.SeaFiltrProd(connect);
						break;
					case 6:
						system("cls");
						inter.Kondorse(connect);
						break;
					case 7:
						while (1)
						{
							system("cls");
							M.control_acc();
							cout << "Ваш выбор: "; choice = klient.checkDatai(connect);
							switch (choice)
							{
							case 1:
								system("cls");
								inter.AddAcc(connect);
								break;
							case 2:
								system("cls");
								connect.RecvStr(UserStatus);
								if (strcmp(UserStatus, "MAIN") == 0)
									inter.AddAcc(connect);
								else
								{
									cout << "Данная функция доступна пользователю со статусом MAIN" << endl;
									Sleep(1500);
								}
								break;
							case 3:
								system("cls");
								inter.OutPutAcc(connect);
								system("pause");
								break;
							case 4:
								system("cls");
								inter.DeleteAcc(connect);
								break;
							default: break;
							}
							if (choice == 5)
								break;
						}
						choice = 0;
						break;
					default: break;
					}
					if (choice == 8)
						break;
				}
				break;
			case 2:
				while (1)
				{
					system("cls");
					M.expert_menu(connect);
					cout << "Ваш выбор: "; choice = klient.checkDatai(connect);
					switch (choice)
					{
					case 1:
						system("cls");
						inter.OutputAllProd(connect);
						system("pause");
						break;
					case 2:
						system("cls");
						inter.SeaFiltrProd(connect);
						break;
					case 3:
						system("cls");
						inter.AddReview(connect);
						break;
					case 4:
						system("cls");
						inter.OutputReview(connect);
						break;
					default: break;
					}
					if (choice == 5)
						break;
				}
				choice = 0;
				break;
			case 3:
				while (1)
				{
					system("cls");
					M.user_menu(connect);
					cout << "Ваш выбор: "; choice = klient.checkDatai(connect);
					switch (choice)
					{
					case 1:
						system("cls");
						inter.OutputProdUser(connect);
						system("pause");
						break;
					case 2:
						system("cls");
						inter.SeaFiltrProdUser(connect);
						break;
					case 3:
						system("cls");
						inter.KondorseUser(connect);
						break;
					default: break;
					}
					if (choice == 4)
						break;
				}
				choice = 0;
				break;
			default: break;
			}
			choice = 0;
			break;
		case 2:
			system("cls");
			inter.AddAcc(connect);
			break;
		case 3:
			system("cls");
			cout << "Выход из программы" << endl;
			break;
		}
		if (choice == 3)
			break;
	}
	delete[] UserStatus;
	return 0;
}
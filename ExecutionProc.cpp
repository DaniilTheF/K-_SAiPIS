#include "ExecutionProc.h"

void ExecutionProc::AddAcc(Connection& connect)
{
	char* buf = new char[100];
	connect.RecvStr(buf);
	cout << "\tРегистрация <" << buf << ">" << endl;
	cout << "Фамилия: "; klient.setStr(connect);
	cout << "Имя: "; klient.setStr(connect);
	cout << "Отчество: "; klient.setStr(connect);
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
			cout << "Login должен содержать 6 или более символов" << endl;
		else if (k == 2)
			cout << "Login может содержать латинские буквы, цифры и специальные символы(-._)" << endl;
		else if (k == 3)
			cout << "Данный Login занят другим пользователем" << endl;
		if (k != 0)
			cout << "Введите Login: ";
	} while (k != 0);
}

void ExecutionProc::OutPutAcc(Connection& connect)
{
	char* buf = new char[100];
	int n = connect.RecvInt();
	klient.setLine(111, '='); cout << endl;
	cout << "|" << setw(5) << "  #" << "|" << setw(15) << "Status" << "|" << setw(20) << "Login" << "|"
		<< setw(20) << "Password" << "|" << setw(45) << "ФИО" << "|" << endl;
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
		else { cout << "|" << setw(20) << "НЕДОСТУПНО"; }
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
		cout << "Номер записи, которую хотите удалить(0 - вернуться назад): ";
		choice = klient.checkDatai(connect);
		if (choice != 0)
		{
			choice = connect.RecvInt();
			if (choice == 1)
			{
				cout << "Нельзя удалить собственную учетную запись" << endl;
				Sleep(2000);
			}
			else if (choice == 2)
			{
				cout << "" << endl;
				Sleep(2000);
			}
			else
			{
				cout << "Вы подтверждаете удаление? (1 - ДА / 2 - НЕТ):";
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
			cout << "Неправильный логин или пароль!" << endl;
			cout << "Для повторного ввода пароля введите 1 или для выхода введите 2:" << endl;
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
		cout << "При добавлении  ассортимента товарной продукции будут удалены ранжирования экспертов" << endl;
		cout << "1. Добавить продукт" << endl;
		cout<< "2. Не добавлять продукт" << endl;
		cout << "Ваш выбор: ";
		choice = klient.checkDatai(connect);
	}
	if (choice != 2)
	{
		setType(connect); // для заполнения типа продукта
		cout << "Сведения о типе продукта: ";
		klient.setStr(connect);
		setDemand(connect); // для заполнения спроса продукции
		cout << "Стоимость продукта при продаже (тыс. денежных ед.): ";
		klient.checkDatad(connect);
		cout << "Ожидаемые кол-во проданной продукции: ";
		klient.checkDatai(connect);
		cout << "Затраты на внедрение продукции: ";
		klient.checkDatad(connect);;
	}
}

void ExecutionProc::setType(Connection& connect)
{
	cout << "\tВиды продуктов" << endl;
	cout << "1 - Овощи" << endl;
	cout << "2 - Фрукты" << endl;
	cout << "3 - Мясо" << endl;
	cout << "Ваш выбор: ";  klient.checkDatai(connect);
}

void ExecutionProc::setDemand(Connection& connect)
{
	cout << "\tСпрос на продукцию на рынке" << endl;
	cout << "1 - Высокий" << endl;
	cout << "2 - Средний" << endl;
	cout << "3 - Низкий" << endl;
	cout << "Ваш выбор: "; klient.checkDatai(connect);
}
				
void ExecutionProc::OutputProd()
{
	klient.setLine(207, '='); cout << endl;
	cout << "|" << setw(3) << "#  " << "|" << setw(10) << "Вид прод. " << "|"
		<< setw(25) << "Краткая информация о прод. " << "|" << setw(32)
		<< " Спрос на прод. на рынке " << "|" << setw(23) << " Стоимость прод. при продаже: " << "|" << setw(25)
		<< " Ожидаемые кол-во проданной прод.: " << "|" << setw(15) << " Затраты на внедрение прод. " << "|" << setw(30) << " Ожидаемый доход с проданной прод." << "|" << endl;
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
	else { cout << "Нет записей" << endl; Sleep(1500); }
	delete[] str1;
}

void ExecutionProc::OutputProdUser(Connection& connect) {
	char* str1 = new char[100];
	int n = connect.RecvInt();
	if (n > 0)
	{

		klient.setLine(207, '='); cout << endl;
		cout << "|" << setw(3) << "#  " << "|" << setw(10) << "Вид продкта " << "|"
			<< setw(26) << "Краткая информация о продукте "
			"|" << setw(19) << " Стоимость продукции:  " << "|" << endl;
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
	else { cout << "Нет записей" << endl; Sleep(1500); }
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
			cout << "Номер записи, которую хотите изменить(0 - вернуться назад): ";
			choice = klient.checkDatai(connect);
			if (choice != 0)
			{
				cout << "\tКритерии редактирования" << endl;
				cout << "1 - Вид продукции" << endl;
				cout << "2 - Общие сведения" << endl;
				cout << "3 - Спрос на продукции на рынке " << endl;
				cout << "4 - Данные влияющие на доход" << endl;
				cout << "Ваш выбор: "; int edit = klient.checkDatai(connect);
				switch (edit)
				{
				case 1:
					cout << "Вид продукции: ";
					setType(connect);
					break;
				case 2:
					klient.setStr(connect);
					break;
				case 3:
					cout << "Спрос продукции на рынке: ";
					setDemand(connect);
					break;
				case 4:
					cout << " Стоимость продукта при продаже(тыс.денежных ед.) :";
					klient.checkDatad(connect);
					cout << "Ожидаемые кол-во проданной продукции: ";
					klient.checkDatai(connect);
					cout << "Затраты на внедрение продукции: ";
					klient.checkDatad(connect);
					break;
				}
			}
		} while (choice != 0);
	}
	else
	{
		cout << "Нет записей" << endl;
		Sleep(1500);
	}
}

void ExecutionProc::DeleteProd(Connection& connect)
{
	int choice = 0;

	if (connect.RecvInt() > 0)
	{
		cout << "Предупреждение!" << endl;
		cout << "При удалении ассортимента товарной продукции будут удалены ранжирования экспертов" << endl;
		cout << "1. Удалить продукт" << endl;
		cout << "2. Не удалять продукт" << endl;
		cout << "Ваш выбор: "; choice = klient.checkDatai(connect);
	}
	if (choice != 2)
	{
		if (connect.RecvInt() > 0)
		{
			do {
				system("cls");
				OutputAllProd(connect);
				cout << "Номер записи, которую хотите удалить(0 - вернуться назад): ";
				choice = klient.checkDatai(connect);
				if (choice != 0)
				{
					cout << "Вы подтверждаете удаление? 1 - Да | 2 - Нет:";
					int del = klient.checkDatai(connect);
				}
			} while (choice != 0);
		}
		else
		{
			cout << "Нет записей" << endl;
			Sleep(1500);
		}
	}
}

void ExecutionProc::SeaFiltrProd(Connection& connect)
{
	if (connect.RecvInt() > 0)
	{
		cout << "\tПоиск и фильтрация" << endl;
		cout << "1 - Поиск по виду продукции" << endl;
		cout << "2 - Поиск по общим сведниям" << endl;
		cout << "3 - Поиск по спросу на рынке" << endl;
		cout << "4 - Фильтрация по стоимости продукта" << endl;
		cout << "5 - Фильтрация по количеству проданного продукта" << endl;
		cout << "6 - Фильтрация по затратам на внедрение" << endl;
		cout << "Ваш выбор: "; int choice = klient.checkDatai(connect);
		switch (choice)
		{
		case 1:
			setType(connect);
			break;
		case 2:
			cout << "Общие сведения: ";
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
		cout << "Нет записей" << endl;
		Sleep(1500);
	}
}

void ExecutionProc::SeaFiltrProdUser(Connection& connect) {
	if (connect.RecvInt() > 0)
	{
		cout << "\tПоиск и фильтрация" << endl;
		cout << "1 - Поиск по виду продукции" << endl;
		cout << "2 - Поиск по общим сведниям" << endl;
		cout << "3 - Фильтрация по стоимости продукта" << endl;
		cout << "Ваш выбор: "; int choice = klient.checkDatai(connect);
		switch (choice)
		{
		case 1:
			setType(connect);
			break;
		case 2:
			cout << "Общие сведения: ";
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
		cout << "|" << setw(3) << "#  " << "|" << setw(10) << "Вид продкта " << "|"
			<< setw(26) << "Краткая информация о продукте "
			"|" << setw(19) << " Стоимость продукции:  " << "|" << endl;
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
		cout << "Нет записей" << endl;
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
		cout << "\t\t\tРанжирование альтернатив" << endl;
		for (int i = 0; i < counter; i++)
		{
			do {
				k = 0;
				cout << i + 1 << ") место(альтернативы): ";
				klient.checkDatai(connect);
				k = connect.RecvInt();
				if (k != 0)
				{
					cout << "Данная альтернатива уже использована!" << endl;
				}
			} while (k != 0);
		}
	}
	else { cout << "Нет ассортимента товарной продукции" << endl; Sleep(1500); }
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
			cout << "Ваши оценки Aij, характеризующие предпочтение альтернатив:" << endl;
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
			cout << "Вы считаете, что наилучшим ассортиментом товарной продукции является: ";
			cout << "объект: " << connect.RecvInt() << endl;
			system("pause");
		}
		else
		{
			cout << "Вы не осуществляли ранжирование альтернатив " << endl;
			Sleep(3000);
		}
	}
	else
	{
		cout << "Вы не осуществляли ранжирование альтернатив " << endl;
		cout << "либо администратор внес изменения в список ассортиментов товарной продукции" << endl;
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

		cout << "По мнению экспертов наилучшей альтернативой по выбору ассортимента товарной продукции является: ";
		cout << "объект: " << connect.RecvInt() << endl;
		system("pause");
	}
	else { cout << "Эксперты еще не ранжировали альтернативы" << endl; Sleep(2000); }
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

		cout << "По мнению экспертов наилучшей альтернативой по выбору ассортимента товарной продукции является: ";
		cout << "объект #" << connect.RecvInt() << endl;
		system("pause");
	}
	else { cout << "Эксперты еще не ранжировали альтернативы" << endl; Sleep(2000); }
}
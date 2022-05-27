#include "Connection.h"
#include "Accounts.h"
#include "Autorization.h"
#include "ExecutionProc.h"
int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice, autho = 0;
	ExecutionProc inter;
	Autorization aut;
	Connection connect;
	aut.Read();
	aut.ReadReview();
	inter.Read();
	inter.ReadReview();
	connect.acept();
	connect.SendInt(aut.vecUserSize());
	if (aut.vecUserSize() == 0)
		aut.Add("MAIN", connect);
	while (1)
	{
		choice = serv.Datacheck(1, 3, connect);
		switch (choice)
		{
		case 1:
			autho = aut.Authorizatio(connect);
			switch (autho)
			{
			case 1:
				while (1)
				{
					connect.SendStr(aut.UserStatus);
					connect.SendStr(aut.UserLogin);
					choice = serv.Datacheck(1, 8, connect);
					switch (choice)
					{
					case 1:
						inter.Add(connect);
						break;
					case 2:
						inter.EditProd(connect);
						break;
					case 3:
						inter.OutPut(connect);
						break;
					case 4:
						inter.DeleteProd(connect);
						break;
					case 5:
						inter.SeaFiltrProd(connect);
						break;
					case 6:
						inter.Kondorse(connect);
						break;
					case 7:
						while (1)
						{
							choice = serv.Datacheck(1, 5, connect);
							switch (choice)
							{
							case 1:
								aut.Add("EXPERT", connect);
								break;
							case 2:
								connect.SendStr(aut.UserStatus);
								if (strcmp(aut.UserStatus, "MAIN") == 0)
								{
									aut.Add("ADMIN", connect);
								}
								break;
							case 3:
								aut.Output(connect);
								break;
							case 4:
								aut.DeleteAcc(connect);
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
				choice = 0;
				break;
			case 2:
				while (1)
				{
					connect.SendStr(aut.UserStatus);
					connect.SendStr(aut.UserLogin);
					choice = serv.Datacheck(1, 5, connect);
					switch (choice)
					{
					case 1:
						inter.OutPut(connect);
						break;
					case 2:
						inter.SeaFiltrProd(connect);
						break;
					case 3:
						inter.AddReview(connect);
						break;
					case 4:
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
					connect.SendStr(aut.UserStatus);
					connect.SendStr(aut.UserLogin);
					choice = serv.Datacheck(1, 4, connect);
					switch (choice)
					{
					case 1:
						inter.OutputProdUser(connect);
						break;
					case 2:
						inter.SeaFiltrProdUser(connect);
						break;
					case 3:
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
			aut.Add("USER", connect);
			break;
		case 3:
			aut.Write();
			aut.WriteReview();
			inter.Write();
			inter.WriteReview();
			break;
		}
		if (choice == 3)
			break;
	}
	return 0;
}
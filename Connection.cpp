#include "Connection.h"

void Connection::conect()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Ошибка загрузки библиотеки wsaData" << endl;
		exit(1);
	}
	int SizeOfAddr = sizeof(addr);
	this->addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->addr.sin_port = htons(1111);
	this->addr.sin_family = AF_INET;
	this->connection = socket(AF_INET, SOCK_STREAM, NULL);
	cout << "Нажмите любую клавишу чтобы подключится к серверу..." << endl; _getch();
	if (connect(this->connection, (SOCKADDR*)&addr, SizeOfAddr) != 0)
	{
		cout << "ERROR: не удалось подключится к серверу!" << endl;
		exit(1);
	}
	else { cout << "Подключение к серверу произошло успешно!" << endl; }
}

void Connection::SendStr(const char* buf)
{
	int msg_size = strlen(buf);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, buf, msg_size, NULL);
}

void Connection::RecvStr(char*& data)
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1]; msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	strcpy(data, msg); delete[] msg;
}

void Connection::SendInt(int buf)
{
	char* str = new char[20]; itoa(buf, str, 10);
	int msg_size = strlen(str);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, str, msg_size, NULL);
	delete[] str;
}

int Connection::RecvInt()
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1]; msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	int buf = atoi(msg); delete[] msg;
	return buf;
}

void Connection::SendDouble(double buf)
{
	char* str = new char[50]; sprintf(str, "%.2f", buf);
	int msg_size = strlen(str);
	send(this->connection, (char*)&msg_size, sizeof(int), NULL);
	send(this->connection, str, msg_size, NULL);
	delete[] str;
}

double Connection::RecvDouble()
{
	int msg_size = 0;
	recv(this->connection, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1]; msg[msg_size] = '\0';
	recv(this->connection, msg, msg_size, NULL);
	double buf = atof(msg); delete[] msg;
	return buf;
}
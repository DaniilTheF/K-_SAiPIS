#pragma once
#include "Connection.h"
#include <vector>
#include "ProductRange.h"
#include "ExecutionProc.h"

using namespace std;
class Autorization : public ABS
{
	vector<User> vectUser;
	vector<Review> vectreview;
public:
	char* UserStatus = new char[100];
	char* UserLogin = new char[100];

	int vecUserSize() { return vectUser.size(); };
	void Read();
	void Write();
	void Add(const char*, Connection&);
	void setLogin(char*&, Connection&);
	void Output(Connection&);
	void DeleteAcc(Connection&);
	int Authorizatio(Connection&);

	void ReadReview();
	void WriteReview();
};


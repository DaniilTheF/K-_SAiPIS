#pragma once
#include "Connection.h"
#include "Accounts.h"
#include "ProductRange.h"
#include "Review.h"
#include "ABS.h"
#include <fstream>
#include <vector>

class ExecutionProc : public ABS
{
private:
	//vector<User> vectUser;
	vector<ProductRange> vectProd;
	vector<Review> vectReview;
public:
	/*char* UserStatus = new char[100];
	char* UserLogin = new char[100];

	int vecUserSize() { return vectUser.size(); };
	void ReadAcc();
	void WriteAcc();
	void AddAcc(const char*, Connection&);
	void setLogin(char*&, Connection&);
	void OutputAcc(Connection&);
	void DeleteAcc(Connection&);

	int Authorization(Connection&);*/
	char* UserStatus = new char[100];
	char* UserLogin = new char[100];
	void Read();
	void Write();
	void Add(Connection&);
	void setType(char*&, Connection&);
	void setDemand(char*&, Connection&);
	void OutPut(Connection&);
	void EditProd(Connection&);
	void DeleteProd(Connection&);
	void SeaFiltrProd(Connection&);

	void ReadReview();
	void WriteReview();
	void AddReview(Connection&); 
	void OutputReview(Connection&);
	void Kondorse(Connection&);

	void OutputProdUser(Connection&);
	void SeaFiltrProdUser(Connection&);
	void KondorseUser(Connection&);

	~ExecutionProc();
};		
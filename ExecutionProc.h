#pragma once
#include "Connection.h"
#include "CheckNumb.h"
#include <iomanip>

class ExecutionProc
{
public:
	void setLogin(Connection&);
	void AddAcc(Connection&);
	void OutPutAcc(Connection&);
	void DeleteAcc(Connection&);
	int Authorization(Connection&);

	void setType(Connection&);
	void setDemand(Connection&);
	void AddProd(Connection&);
	void OutputProd();
	void OutputAllProd(Connection&);
	void EditProd(Connection&);
	void DeleteProd(Connection&);
	void SeaFiltrProd(Connection&);

	void AddReview(Connection&);
	void OutputReview(Connection&);
	void Kondorse(Connection&);

	void OutputProdUser(Connection&);
	void SeaFiltrProdUser(Connection&);
	void KondorseUser(Connection&);
};
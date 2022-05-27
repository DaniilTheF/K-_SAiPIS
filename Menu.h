#pragma once
#include "ExecutionProc.h"

class Menu
{
public:
	void main_menu();
	void admin_menu(Connection&);
	void expert_menu(Connection&);
	void user_menu(Connection&);
	void control_acc();
};
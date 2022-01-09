#pragma once
#include "stdafx.h"
#include "CMenu.h"

#include "MultiGumballMachineWithState.h"

class GumballMachine
{
public:
	GumballMachine();
	void Start();
private:
	void Refill(std::istream& in);

	CMenu m_menu;
	with_state::MultiGumballMachineWithState m_gumballMachine;
};


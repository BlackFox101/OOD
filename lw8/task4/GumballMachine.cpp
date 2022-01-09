#include "stdafx.h"
#include "GumballMachine.h"

using namespace std;
using namespace placeholders;

GumballMachine::GumballMachine()
	: m_gumballMachine(with_state::MultiGumballMachineWithState(0))
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	m_menu.AddItem("info", "GumBall machine info", [this](istream&) { cout << m_gumballMachine.ToString() << endl; });
	m_menu.AddItem("insertQuarter", "Insert Quarter", [this](istream&) { m_gumballMachine.InsertQuarter(); });
	m_menu.AddItem("ejectQuarter", "EjectQuarter", [this](istream&) { m_gumballMachine.EjectQuarter(); });
	m_menu.AddItem("turnCrank", "TurnCrank", [this](istream&) { m_gumballMachine.TurnCrank(); });
	m_menu.AddItem("refill", "Refill. Args: <gumball numbers>", [this](istream& in) { Refill(in); });
}

void GumballMachine::Start()
{
	m_menu.Run();
}

void GumballMachine::Refill(istream& in)
{
	int numBalls;
	in >> numBalls;
	if (in.fail())
	{
		throw invalid_argument("Not enough arguments");
	}
	if (numBalls < 0)
	{
		throw invalid_argument("The gumbals must be greater than zero");
	}
	m_gumballMachine.Refill(numBalls);
}

#include "MultiGumballMachineWithState.h"

with_state::MultiGumballMachineWithState::MultiGumballMachineWithState(unsigned numBalls)
	: m_soldState(*this)
	, m_soldOutState(*this)
	, m_noQuarterState(*this)
	, m_hasQuarterState(*this)
	, m_state(&m_soldOutState)
	, m_gumBallCount(numBalls)
{
	if (m_gumBallCount > 0)
	{
		m_state = &m_noQuarterState;
	}
}

void with_state::MultiGumballMachineWithState::EjectQuarter()
{
	m_state->EjectQuarter();
}

void with_state::MultiGumballMachineWithState::InsertQuarter()
{
	m_state->InsertQuarter();
}

void with_state::MultiGumballMachineWithState::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}

std::string with_state::MultiGumballMachineWithState::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Multi Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
	return (fmt % m_gumBallCount % (m_gumBallCount != 1 ? "s" : "") % m_quarterCount % (m_quarterCount != 1 ? "s" : "") % m_state->ToString()).str();
}

unsigned with_state::MultiGumballMachineWithState::GetBallCount() const
{
	return m_gumBallCount;
}

unsigned with_state::MultiGumballMachineWithState::GetQuarterCount() const
{
	return m_quarterCount;
}

bool with_state::MultiGumballMachineWithState::AddQuarter()
{
	if (m_quarterCount < MAX_QUARTER_COUNT)
	{
		++m_quarterCount;
		return true;
	}
	return false;
}

bool with_state::MultiGumballMachineWithState::RemoveAllQuarter()
{
	if (m_quarterCount != 0)
	{
		m_quarterCount = 0;
		return true;
	}
	return false;
}

bool with_state::MultiGumballMachineWithState::RemoveOneQuarter()
{
	if (m_quarterCount != 0)
	{
		--m_quarterCount;
		return true;
	}
	return false;
}

void with_state::MultiGumballMachineWithState::ReleaseBall()
{
	if (m_gumBallCount != 0)
	{
		std::cout << "A gumball comes rolling out the slot...\n";
		--m_gumBallCount;
	}
}

void with_state::MultiGumballMachineWithState::SetSoldOutState()
{
	m_state = &m_soldOutState;
}

void with_state::MultiGumballMachineWithState::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}

void with_state::MultiGumballMachineWithState::SetSoldState()
{
	m_state = &m_soldState;
}

void with_state::MultiGumballMachineWithState::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}

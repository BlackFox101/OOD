#include "NaiveMultiGumballMachine.h"

naive::CMultiGumballMachine::CMultiGumballMachine(unsigned count)
	: m_gumBallCount(count)
	, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	, m_quarterCount(0)
{
}

void naive::CMultiGumballMachine::InsertQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
		++m_quarterCount;
		cout << "You inserted a quarter\n";
		m_state = State::HasQuarter;
		break;
	case State::HasQuarter:
		if (m_quarterCount < MAX_QUARTER_COUNT)
		{
			++m_quarterCount;
			cout << "You inserted a quarter\n";
		}
		else
		{
			cout << "You can't insert another quarter. You have reached the maximum - " << MAX_QUARTER_COUNT << endl;
		}
		break;
	case State::Sold:
		cout << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void naive::CMultiGumballMachine::EjectQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::HasQuarter:
		m_quarterCount = 0;
		cout << "All quarters returned.\n";
		m_state = State::NoQuarter;
		break;
	case State::NoQuarter:
		cout << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
		cout << "Sorry you already turned the crank\n";
		break;
	case State::SoldOut:
		if (m_quarterCount > 0)
		{
			m_quarterCount = 0;
			cout << "All quarters returned.\n";
		}
		else
		{
			cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
		break;
	}
}

void naive::CMultiGumballMachine::TurnCrank()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		cout << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		cout << "You turned...\n";
		m_state = State::Sold;
		Dispense();
		break;
	case State::Sold:
		cout << "Turning twice doesn't get you another gumball\n";
		break;
	}
}

void naive::CMultiGumballMachine::Refill(unsigned numBalls)
{
	m_gumBallCount = numBalls;
	m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
}

std::string naive::CMultiGumballMachine::ToString() const
{
	std::string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Multi Gumball Model #2016
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
	return (fmt % m_gumBallCount % (m_gumBallCount != 1 ? "s" : "") % m_quarterCount % (m_quarterCount != 1 ? "s" : "") % state).str();
}

void naive::CMultiGumballMachine::Dispense()
{
	using namespace std;
	switch (m_state)
	{
	case State::Sold:
		cout << "A gumball comes rolling out the slot\n";
		--m_quarterCount;
		--m_gumBallCount;
		if (m_gumBallCount == 0)
		{
			cout << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else if (m_quarterCount == 0)
		{
			m_state = State::NoQuarter;
		}
		else
		{
			m_state = State::HasQuarter;
		}
		break;
	case State::NoQuarter:
		cout << "You need to pay first\n";
		break;
	case State::SoldOut:
	case State::HasQuarter:
		cout << "No gumball dispensed\n";
		break;
	}
}

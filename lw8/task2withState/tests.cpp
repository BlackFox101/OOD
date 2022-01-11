#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "MultiGumballMachineWithState.h"

using namespace std;
using namespace with_state;

enum class State
{
	CSoldState,
	CSoldOutState,
	CHasQuarterState,
	CNoQuarterState
};

class TestState 
{
public:
	TestState(State state)
		: m_state(state)
	{}
	string ToString()
	{
		switch (m_state)
		{
		case State::CSoldState:
			return "delivering a gumball";
		case State::CSoldOutState:
			return "sold out";
		case State::CHasQuarterState:
			return "waiting for turn of crank";
		case State::CNoQuarterState:
			return "waiting for quarter";
		default:
			return "sold out";
		}
	}
private:
	State m_state;
};

string ToString(TestState* state, unsigned gumBallCount, unsigned quarterCount)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Multi Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
	return (fmt % gumBallCount % (gumBallCount != 1 ? "s" : "") % quarterCount % (quarterCount != 1 ? "s" : "") % state->ToString()).str();
}

TEST_CASE("Testing with 'SoldOut' state")
{
	MultiGumballMachineWithState m(0);
	TestState soldOutState(State::CSoldOutState);

	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 0));

	WHEN("Insert quarter")
	{
		m.InsertQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(&soldOutState, 0, 0));
		}
	}
	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(&soldOutState, 0, 0));
		}
	}
	WHEN("Turn Crank")
	{
		m.TurnCrank();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(&soldOutState, 0, 0));
		}
	}
}

TEST_CASE("Testing with 'NoQuarter' state")
{
	MultiGumballMachineWithState m(5);
	TestState noQuarterState(State::CNoQuarterState);
	TestState hasQuarterState(State::CHasQuarterState);

	WHEN("Insert quarter")
	{
		m.InsertQuarter();
		THEN("The state has changed. New - 'CHasQuarterState'")
		{
			CHECK(m.ToString() == ToString(&hasQuarterState, 5, 1));
		}
	}
	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
		}
	}
	WHEN("Eject Quarter")
	{
		m.TurnCrank();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
		}
	}
}

TEST_CASE("Testing with 'HasQuarter' state")
{
	GIVEN("5 balls and 1 quarter")
	{
		MultiGumballMachineWithState m(5);
		m.InsertQuarter();
		TestState hasQuarterState(State::CHasQuarterState);
		REQUIRE(m.ToString() == ToString(&hasQuarterState, 5, 1));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter added")
			{
				CHECK(m.ToString() == ToString(&hasQuarterState, 5, 2));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				TestState noQuarterState(State::CNoQuarterState);
				CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0, gumBall count = 4")
			{
				TestState noQuarterState(State::CNoQuarterState);
				CHECK(m.ToString() == ToString(&noQuarterState, 4, 0));
			}
		}
	}

	GIVEN("5 balls and 2 quarters")
	{
		MultiGumballMachineWithState m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		TestState hasQuarterState(State::CHasQuarterState);
		REQUIRE(m.ToString() == ToString(&hasQuarterState, 5, 2));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter added")
			{
				CHECK(m.ToString() == ToString(&hasQuarterState, 5, 3));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				TestState noQuarterState(State::CNoQuarterState);
				CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state will not change. Quarter count = 1, gumBall count = 4")
			{
				CHECK(m.ToString() == ToString(&hasQuarterState, 4, 1));
			}
		}
	}

	GIVEN("5 balls and max(5) quarters")
	{
		MultiGumballMachineWithState m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		TestState hasQuarterState(State::CHasQuarterState);
		REQUIRE(m.ToString() == ToString(&hasQuarterState, 5, 5));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter not added")
			{
				CHECK(m.ToString() == ToString(&hasQuarterState, 5, 5));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				TestState noQuarterState(State::CNoQuarterState);
				CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state will not change. Quarter count = 4, gumBall count = 4")
			{
				CHECK(m.ToString() == ToString(&hasQuarterState, 4, 4));
			}
		}
	}
}

SCENARIO("Add Additional quarters, without waiting for the issuance of all the balls.")
{
	MultiGumballMachineWithState m(5);
	m.InsertQuarter();
	m.InsertQuarter();
	TestState hasQuarterState(State::CHasQuarterState);
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 5, 2));

	m.TurnCrank();
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 4, 1));
	m.InsertQuarter();
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 4, 2));
	m.TurnCrank();
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 3, 1));
}

SCENARIO("The balls are over, the quarters can be taken away.")
{
	MultiGumballMachineWithState m(1);
	m.InsertQuarter();
	m.InsertQuarter();
	TestState hasQuarterState(State::CHasQuarterState);
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 1, 2));

	m.TurnCrank();
	TestState soldOutState(State::CSoldOutState);
	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 1));
	m.EjectQuarter();
	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 0));
}
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "MultiGumballMachineWithState.h"

using namespace std;
using namespace with_state;

string ToString(const with_state::IState* state, unsigned gumBallCount, unsigned quarterCount)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Multi Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
	return (fmt % gumBallCount % (gumBallCount != 1 ? "s" : "") % quarterCount % (quarterCount != 1 ? "s" : "") % state->ToString()).str();
}

TEST_CASE("Add gumballs")
{
	WHEN("Current state - 'SoldOut'")
	{
		MultiGumballMachineWithState m(0);
		with_state::CSoldOutState soldOutState(m);
		REQUIRE(m.ToString() == ToString(&soldOutState, 0, 0));
		m.Refill(1);
		THEN("New state - 'NoQuarter'")
		{
			with_state::CNoQuarterState noQuarterState(m);
			REQUIRE(m.ToString() == ToString(&noQuarterState, 1, 0));
		}
	}
	WHEN("Current state - 'NoQuarter'")
	{
		MultiGumballMachineWithState m(5);
		with_state::CNoQuarterState noQuarterState(m);
		REQUIRE(m.ToString() == ToString(&noQuarterState, 5, 0));
		m.Refill(1);
		THEN("The state will not change")
		{
			REQUIRE(m.ToString() == ToString(&noQuarterState, 1, 0));
		}
	}
	WHEN("Current state - 'HasQuarter'")
	{
		MultiGumballMachineWithState m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		with_state::CHasQuarterState hasQuarterState(m);
		REQUIRE(m.ToString() == ToString(&hasQuarterState, 5, 2));
		m.Refill(1);
		THEN("The state will not change")
		{
			with_state::CHasQuarterState hasQuarterState(m);
			REQUIRE(m.ToString() == ToString(&hasQuarterState, 1, 2));
		}
	}
}

TEST_CASE("Testing with 'SoldOut' state")
{
	MultiGumballMachineWithState m(0);
	with_state::CSoldOutState soldOutState(m);

	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 0));

	WHEN("Insert  quarter")
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
	with_state::CNoQuarterState noQuarterState(m);
	with_state::CHasQuarterState hasQuarterState(m);

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
		with_state::CHasQuarterState hasQuarterState(m);
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
				with_state::CNoQuarterState noQuarterState(m);
				CHECK(m.ToString() == ToString(&noQuarterState, 5, 0));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0, gumBall count = 4")
			{
				with_state::CNoQuarterState noQuarterState(m);
				CHECK(m.ToString() == ToString(&noQuarterState, 4, 0));
			}
		}
	}

	GIVEN("5 balls and 2 quarters")
	{
		MultiGumballMachineWithState m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		with_state::CHasQuarterState hasQuarterState(m);
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
				with_state::CNoQuarterState noQuarterState(m);
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
		with_state::CHasQuarterState hasQuarterState(m);
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
				with_state::CNoQuarterState noQuarterState(m);
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
	with_state::CHasQuarterState hasQuarterState(m);
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
	with_state::CHasQuarterState hasQuarterState(m);
	REQUIRE(m.ToString() == ToString(&hasQuarterState, 1, 2));

	m.TurnCrank();
	with_state::CSoldOutState soldOutState(m);
	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 1));
	m.EjectQuarter();
	REQUIRE(m.ToString() == ToString(&soldOutState, 0, 0));
}
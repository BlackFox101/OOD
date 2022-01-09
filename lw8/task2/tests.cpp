#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "NaiveMultiGumballMachine.h"

using namespace std;
using namespace naive;

enum class State
{
	SoldOut,		// Жвачка закончилась
	NoQuarter,		// Нет монетки
	HasQuarter,		// Есть монетка
	Sold,			// Жвачка выдана
};

string ToString(unsigned gumBallCount, unsigned quarterCount, State state)
{
	std::string stringState =
		(state == State::SoldOut) ? "sold out" :
		(state == State::NoQuarter) ? "waiting for quarter" :
		(state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Multi Gumball Model #2016
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
	return (fmt % gumBallCount % (gumBallCount != 1 ? "s" : "") % quarterCount % (quarterCount != 1 ? "s" : "") % stringState).str();
}

TEST_CASE("Testing with 'SoldOut' state")
{
	CMultiGumballMachine m(0);
	REQUIRE(m.ToString() == ToString(0, 0, State::SoldOut));

	WHEN("Insert  quarter")
	{
		m.InsertQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(0, 0, State::SoldOut));
		}
	}

	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(0, 0, State::SoldOut));
		}
	}

	WHEN("Turn Crank")
	{
		m.TurnCrank();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToString(0, 0, State::SoldOut));
		}
	}
}

TEST_CASE("Testing with 'NoQuarter' state")
{
	CMultiGumballMachine m(5);
	REQUIRE(m.ToString() == ToString(5, 0, State::NoQuarter));

	WHEN("Insert quarter")
	{
		m.InsertQuarter();
		THEN("The state has changed. New - 'CHasQuarterState'")
		{
			CHECK(m.ToString() == ToString(5, 1, State::HasQuarter));
		}
	}

	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToString(5, 0, State::NoQuarter));
		}
	}

	WHEN("Eject Quarter")
	{
		m.TurnCrank();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToString(5, 0, State::NoQuarter));
		}
	}
}

TEST_CASE("Testing with 'HasQuarter' state")
{
	GIVEN("5 balls and 1 quarter")
	{
		CMultiGumballMachine m(5);
		m.InsertQuarter();
		REQUIRE(m.ToString() == ToString(5, 1, State::HasQuarter));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter added")
			{
				CHECK(m.ToString() == ToString(5, 2, State::HasQuarter));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				CHECK(m.ToString() == ToString(5, 0, State::NoQuarter));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0, gumBall count = 4")
			{
				CHECK(m.ToString() == ToString(4, 0, State::NoQuarter));
			}
		}
	}

	GIVEN("5 balls and 2 quarters")
	{
		CMultiGumballMachine m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		REQUIRE(m.ToString() == ToString(5, 2, State::HasQuarter));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter added")
			{
				CHECK(m.ToString() == ToString(5, 3, State::HasQuarter));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				CHECK(m.ToString() == ToString(5, 0, State::NoQuarter));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state will not change. Quarter count = 1, gumBall count = 4")
			{
				CHECK(m.ToString() == ToString(4, 1, State::HasQuarter));
			}
		}
	}

	GIVEN("5 balls and max(5) quarters")
	{
		CMultiGumballMachine m(5);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		REQUIRE(m.ToString() == ToString(5, 5, State::HasQuarter));
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("The state will not change, quarter not added")
			{
				CHECK(m.ToString() == ToString(5, 5, State::HasQuarter));
			}
		}
		WHEN("Eject Quarter")
		{
			m.EjectQuarter();
			THEN("The state has changed. New - 'NoQuarter'. Quarter count = 0")
			{
				CHECK(m.ToString() == ToString(5, 0, State::NoQuarter));
			}
		}
		WHEN("Turn Crank")
		{
			m.TurnCrank();
			THEN("The state will not change. Quarter count = 4, gumBall count = 4")
			{
				CHECK(m.ToString() == ToString(4, 4, State::HasQuarter));
			}
		}
	}
}

SCENARIO("Add Additional quarters, without waiting for the issuance of all the balls.")
{
	CMultiGumballMachine m(5);
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == ToString(5, 2, State::HasQuarter));
	
	m.TurnCrank();
	REQUIRE(m.ToString() == ToString(4, 1, State::HasQuarter));
	m.InsertQuarter();
	REQUIRE(m.ToString() == ToString(4, 2, State::HasQuarter));
	m.TurnCrank();
	REQUIRE(m.ToString() == ToString(3, 1, State::HasQuarter));
}

SCENARIO("The balls are over, the quarters can be taken away.")
{
	CMultiGumballMachine m(1);
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == ToString(1, 2, State::HasQuarter));

	m.TurnCrank();
	REQUIRE(m.ToString() == ToString(0, 1, State::SoldOut));
	m.EjectQuarter();
	REQUIRE(m.ToString() == ToString(0, 0, State::SoldOut));
}
#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "CGumballMachine.h"

using namespace std;

string ToStringWithStateAndBallsCount(const with_state::IState* state, unsigned count)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");

	return (fmt % count % (count != 1 ? "s" : "") % state->ToString()).str();
}

TEST_CASE("Testing with 'SoldOut' state")
{
	CGumballMachine m(0);
	with_state::CSoldOutState soldOutState(m);

	REQUIRE(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));

	WHEN("Insert  quarter")
	{
		m.InsertQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));
		}
	}

	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));
		}
	}

	WHEN("Turn Crank")
	{
		m.TurnCrank();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));
		}
	}
}

TEST_CASE("Testing with 'NoQuarter' state")
{

	CGumballMachine m(5);
	with_state::CNoQuarterState noQuarterState(m);
	with_state::CHasQuarterState hasQuarterState(m);

	REQUIRE(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 5));

	WHEN("Insert  quarter")
	{
		m.InsertQuarter();
		THEN("The state has changed. New - 'CHasQuarterState'")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&hasQuarterState, 5));
		}
	}

	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 5));
		}

	}

	WHEN("Turn Crank")
	{
		m.TurnCrank();
		THEN("The state will not change'")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 5));
		}
	}
}

TEST_CASE("Testing with 'HasQuarter' state")
{
	CGumballMachine m(5);
	m.InsertQuarter();
	with_state::CNoQuarterState noQuarterState(m);
	with_state::CHasQuarterState hasQuarterState(m);
	with_state::CSoldOutState soldOutState(m);

	REQUIRE(m.ToString() == ToStringWithStateAndBallsCount(&hasQuarterState, 5));

	WHEN("Insert quarter")
	{
		m.InsertQuarter();
		THEN("The state will not change")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&hasQuarterState, 5));
		}
	}

	WHEN("Eject Quarter")
	{
		m.EjectQuarter();
		THEN("The state has changed. New - 'CNoQuarterState'")
		{
			CHECK(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 5));
		}

	}

	WHEN("Turn Crank")
	{
		WHEN("There's still some gum ball")
		{
			CGumballMachine m(5);
			m.InsertQuarter();
			m.TurnCrank();
			THEN("The state has changed. New - 'CSoldState'")
			{
				CHECK(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 4));
			}
		}

		WHEN("There was the last gum ball")
		{
			CGumballMachine m(1);
			m.InsertQuarter();
			m.TurnCrank();
			THEN("The state has changed. New - 'CSoldState'")
			{
				CHECK(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));
			}
		}
	}
}
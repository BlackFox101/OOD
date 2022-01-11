#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../gumball_machine/GumBallMachineWithState.h"

using namespace std;

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
	{
	}
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

string ToStringWithStateAndBallsCount(TestState* state, unsigned count)
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
	with_state::CGumballMachine m(0);
	TestState soldOutState(State::CSoldOutState);

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

	with_state::CGumballMachine m(5);
	TestState noQuarterState(State::CNoQuarterState);
	TestState hasQuarterState(State::CHasQuarterState);

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
	with_state::CGumballMachine m(5);
	m.InsertQuarter();
	TestState noQuarterState(State::CNoQuarterState);
	TestState hasQuarterState(State::CHasQuarterState);
	TestState soldOutState(State::CSoldOutState);

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
			with_state::CGumballMachine m(5);
			m.InsertQuarter();
			m.TurnCrank();
			THEN("The state has changed. New - 'CSoldState'")
			{
				CHECK(m.ToString() == ToStringWithStateAndBallsCount(&noQuarterState, 4));
			}
		}

		WHEN("There was the last gum ball")
		{
			with_state::CGumballMachine m(1);
			m.InsertQuarter();
			m.TurnCrank();
			THEN("The state has changed. New - 'CSoldState'")
			{
				CHECK(m.ToString() == ToStringWithStateAndBallsCount(&soldOutState, 0));
			}
		}
	}
}
#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace with_state
{

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;
	virtual unsigned GetQuarterCount() const = 0;

	virtual bool AddQuarter() = 0;
	virtual bool RemoveAllQuarter() = 0;
	virtual bool RemoveOneQuarter() = 0;
	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		m_gumballMachine.RemoveOneQuarter();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else if (m_gumballMachine.GetQuarterCount() == 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetHasQuarterState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IGumballMachine& m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.RemoveAllQuarter())
		{
			std::cout << "All quarters returned.\n";
		}
		else
		{
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
private:
	IGumballMachine& m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.AddQuarter())
		{
			std::cout << "You inserted a quarter\n";
		}
		else
		{
			std::cout << "You can't insert another quarter. You have reached the maximum - " << m_gumballMachine.GetQuarterCount() << std::endl;
		}
	}
	void EjectQuarter() override
	{
		m_gumballMachine.RemoveAllQuarter();
		std::cout << "Quarters returned\n";
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
private:
	IGumballMachine& m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.AddQuarter())
		{
			std::cout << "You inserted a quarter\n";
		}
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
private:
	IGumballMachine& m_gumballMachine;
};

class MultiGumballMachineWithState : private IGumballMachine
{
public:
	MultiGumballMachineWithState(unsigned numBalls);
	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);;
	std::string ToString() const;
private:
	unsigned GetBallCount() const override;
	unsigned GetQuarterCount() const override;
	bool AddQuarter() override;
	bool RemoveAllQuarter() override;
	bool RemoveOneQuarter() override;

	virtual void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;
private:
	const int MAX_QUARTER_COUNT = 5;
	unsigned m_gumBallCount = 0;
	unsigned m_quarterCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
};
}
#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CMultiGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Жвачка выдана
	};

	CMultiGumballMachine(unsigned count);
	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString() const;

private:
	const int MAX_QUARTER_COUNT = 5;

	void Dispense();
	unsigned m_gumBallCount; // Количество шариков
	unsigned m_quarterCount; // Количество монет
	State m_state = State::SoldOut;
};
}



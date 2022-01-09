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
		SoldOut,		// ������ �����������
		NoQuarter,		// ��� �������
		HasQuarter,		// ���� �������
		Sold,			// ������ ������
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
	unsigned m_gumBallCount; // ���������� �������
	unsigned m_quarterCount; // ���������� �����
	State m_state = State::SoldOut;
};
}



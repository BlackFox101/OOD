#pragma once

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly()
	{
		cout << "Flight number " << m_flight_number << endl;
		m_flight_number++;
	}

private:
	int m_flight_number = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		cout << "I'm flying with wings! ";
		IFlyBehavior::Fly();
	}
};

class FlyWithJetEngine : public IFlyBehavior
{
public:
	void Fly() override
	{
		cout << "I'm flying et engine!";
		IFlyBehavior::Fly();
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

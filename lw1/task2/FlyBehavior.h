#pragma once

using namespace std;

struct FlyBehavior
{
	virtual ~FlyBehavior() {};
	virtual void Fly()
	{
		cout << "Flight number " << m_flight_number << endl;
		m_flight_number++;
	}

private:
	int m_flight_number = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
	void Fly() override
	{
		cout << "I'm flying with wings! ";
		FlyBehavior::Fly();
	}
};

class FlyWithJetEngine : public FlyBehavior
{
public:
	void Fly() override
	{
		cout << "I'm flying et engine!";
		FlyBehavior::Fly();
	}
};

class FlyNoWay : public FlyBehavior
{
public:
	void Fly() override {}
};

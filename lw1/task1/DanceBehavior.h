#pragma once

using namespace std;

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class Waltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm waltzing!" << endl;
	}
};

class Minuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing a minuet!" << endl;
	}
};

class DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};
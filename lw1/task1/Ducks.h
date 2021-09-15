#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

using namespace std;

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior, unique_ptr<IQuackBehavior>&& quackBehavior, unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(move(flyBehavior));
		SetDanceBehavior(move(danceBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}

	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	void SetDanceBehavior(unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = move(danceBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck(): Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceWaltz>())
	{}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck(): Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceMinuet>())
	{}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck() : Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWay>())
	{}

	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck(): Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<DanceNoWay>())
	{}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck() : Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
	{}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};
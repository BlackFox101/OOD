#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

typedef function<void()> FlyFunction;
typedef function<void()> QuackFunction;
typedef function<void()> DanceFunction;

using namespace std;

class Duck
{
public:
	Duck(FlyFunction&& flyBehavior, QuackFunction&& quackBehavior, DanceFunction&& danceBehavior)
	{
		SetFlyBehavior(move(flyBehavior));
		SetQuackBehavior(move(quackBehavior));
		SetDanceBehavior(move(danceBehavior));
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(function<void()>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	void SetQuackBehavior(function<void()>&& quackBehavior)
	{
		assert(quackBehavior);
		m_quackBehavior = move(quackBehavior);
	}
	void SetDanceBehavior(function<void()>&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = move(danceBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyFunction m_flyBehavior;
	QuackFunction m_quackBehavior;
	DanceFunction m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck() : Duck(FlyWithWings, QuackBehavior, DanceWaltz)
	{}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck() : Duck(FlyWithWings, QuackBehavior, DanceMinuet)
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck() : Duck(FlyNoWay, MuteQuackBehavior, DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck() : Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck() : Duck(FlyNoWay, QuackBehavior, DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};
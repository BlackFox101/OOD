#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

enum class CoffeePortion
{
	Standart,
	Double
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		: CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

std::string GetCoffeePortionName(CoffeePortion portion)
{
	return std::string(portion == CoffeePortion::Standart ? "Standart" : "Double");
}

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeePortion portion = CoffeePortion::Standart)
		: m_portion(portion),
		CCoffee(GetCoffeePortionName(portion) + " Cappuccino")
	{
	}

	double GetCost() const override 
	{
		return m_portion == CoffeePortion::Standart ? 80 : 120;
	}

private:
	CoffeePortion m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion portion = CoffeePortion::Standart)
		: m_portion(portion),
		CCoffee(GetCoffeePortionName(portion) + " Latte")
	{}

	double GetCost() const override 
	{
		return m_portion == CoffeePortion::Standart ? 90 : 130;
	}

private:
	CoffeePortion m_portion;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(std::string description = "Tea")
		: CBeverage(description)
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Черный чай
class CBlackTea : public CTea
{
public:
	CBlackTea()
		: CTea("Black tea")
	{}
};

// Зеленый чай
class CGreenTea : public CTea
{
public:
	CGreenTea()
		: CTea("Green tea")
	{}
};

// Индийский чай
class СIndianTea : public CTea
{
public:
	СIndianTea()
		: CTea("Indian tea")
	{}
};

// Грузинский чай
class СGeorgianTea : public CTea
{
public:
	СGeorgianTea()
		: CTea("Georgian Tea")
	{}
};

enum class MilkshakePortion
{
	Little,
	Average,
	Big
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion portion = MilkshakePortion::Average)
		: m_portion(portion),
		CBeverage(GetMilkshakeName(portion) + " Milkshake")
	{}

	double GetCost() const override 
	{ 
		switch (m_portion)
		{
		case MilkshakePortion::Little:
			return 50;
		case MilkshakePortion::Average:
			return 60;
		case MilkshakePortion::Big:
			return 80;
		default:
			return 60;
		}
	}

private:
	MilkshakePortion m_portion;

	std::string GetMilkshakeName(MilkshakePortion portion)
	{
		switch (portion)
		{
		case MilkshakePortion::Little:
			return "Little";
		case MilkshakePortion::Average:
			return "Average";
		case MilkshakePortion::Big:
			return "Big";
		default:
			return "Average";
		}
	}
};

#pragma once
#include "Color.h"
#include "Point.h"
#include "Canvas.h"

class CShape
{
public:
	CShape(Color color, std::string name)
		: m_color(color)
		, m_name(name)
	{
	}

	Color GetColor()
	{
		return m_color;
	}

	std::string GetName()
	{
		return m_name;
	}

	virtual void Draw(ICanvas& canvas) const = 0;

private:
	Color m_color;
	std::string m_name;
};


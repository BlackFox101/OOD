#include "..\..\lw7\task1\CEllipse.h"
#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, const Point& center, int xRadius, int yRadius)
		: CShape(color, "Ellipse")
		, m_center(center)
		, m_xRadius(xRadius)
		, m_yRadius(yRadius)
	{}

	Point GetCenter()
	{
		return m_center;
	}

	int GetHorizontalRadius()
	{
		return m_xRadius;
	}

	int GetVerticalRadius()
	{
		return m_yRadius;
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		canvas.DrawEllipse(m_center, m_xRadius, m_yRadius);
	}

private:
	Point m_center;
	int m_xRadius, m_yRadius;
};


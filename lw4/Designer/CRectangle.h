#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point leftTop, Point rightBottom)
		: CShape(color, "Rectangle")
		, m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
	{
	}

	Point GetLeftTop()
	{
		return m_leftTop;
	}

	Point GetRightBottom()
	{
		return m_rightBottom;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(Point(m_leftTop.x, m_rightBottom.y), m_rightBottom);
		canvas.DrawLine(m_rightBottom, Point(m_rightBottom.x, m_leftTop.y));
		canvas.DrawLine(Point(m_rightBottom.x, m_leftTop.y), m_leftTop);
		canvas.DrawLine(m_leftTop, Point(m_leftTop.x, m_rightBottom.y));
	}

private:
	Point m_leftTop, m_rightBottom;
};


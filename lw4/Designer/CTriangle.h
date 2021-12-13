#pragma once
#include "CShape.h"
class CTriangle : public CShape
{
public:
	CTriangle(Color color, const Point& a, const Point& b, const Point& c)
		: CShape(color, "Triangle")
		, m_vertex1(a)
		, m_vertex2(b)
		, m_vertex3(c)
	{
	}

	Point GetVertex1()
	{
		return m_vertex1;
	}

	Point GetVertex2()
	{
		return m_vertex2;
	}

	Point GetVertex3()
	{
		return m_vertex3;
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};


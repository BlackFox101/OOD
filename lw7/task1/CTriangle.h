#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Point vertex1, Point vertex2, Point vertex3);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void Draw(ICanvas& canvas) override;

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

public:
	Point m_vertex1, m_vertex2, m_vertex3;
};
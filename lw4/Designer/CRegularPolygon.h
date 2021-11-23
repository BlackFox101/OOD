#pragma once
#include "CShape.h"
class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, int vertexCount, Point center, int radius)
		: CShape(color, "Regular polygon")
		, m_vertexCount(vertexCount)
		, m_center(center)
		, m_radius(radius)
	{
	}

	int GetVertexCount()
	{
		return m_vertexCount;
	}

	Point GetCenter()
	{
		return m_center;
	}

	int GetRadius()
	{
		return m_radius;
	}

	void Draw(ICanvas& canvas) const override
	{
		// TODO: make an implementation
	}

private:
	int m_vertexCount;
	Point m_center;
	int m_radius;
};


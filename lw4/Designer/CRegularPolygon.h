#pragma once
#include "CShape.h"
#include <cmath>

#define M_PI 3.14159265358979323846

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, int vertexCount, const Point& center, int radius)
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

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		Point firstPoint = {
			m_center.x - m_radius * cos(0),
			m_center.y - m_radius * sin(0)
		};
		double angleBetweenSides = 2 * M_PI / m_vertexCount;
		for (size_t n = 1; n <= m_vertexCount; n++)
		{
			double angle = n * angleBetweenSides;
			Point secondPoint = {
				m_center.x - m_radius * cos(angle),
				m_center.y - m_radius * sin(angle)
			};
			canvas.DrawLine(firstPoint, secondPoint);
			firstPoint = secondPoint;
		}
	}

private:
	int m_vertexCount;
	Point m_center;
	int m_radius;
};


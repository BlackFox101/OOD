#pragma once
#include "CShape.h"
#include "stdafx.h"

class CTriangle : public CShape
{
public:
	CTriangle(Point vertex1, Point vertex2, Point vertex3);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void Draw(ICanvas& canvas) override;

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};


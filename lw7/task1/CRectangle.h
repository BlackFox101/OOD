#pragma once
#include "CShape.h"
#include "stdafx.h"

class CRectangle : public CShape
{
public:
	CRectangle(const Point& leftTop, const Point& m_rightBottom);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void Draw(ICanvas& canvas) override;

private:
	Point m_leftTop, m_rightBottom;
};


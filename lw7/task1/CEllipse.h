#pragma once
#include "CShape.h"
#include "stdafx.h"

class CEllipse : public CShape
{
public:
	CEllipse(const Point& center, double xRadius, double yRadius);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void Draw(ICanvas& canvas) override;
private:
	Point m_center;
	double m_xRadius, m_yRadius;
};


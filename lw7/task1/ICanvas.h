#pragma once
#include "CommonTypes.h"
#include "stdafx.h"

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetLineWidth(double lineWidth) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void FillPoligon(const std::vector<Point>& points, RGBAColor color) = 0;
	virtual void DrawEllipse(const Point& center, double xRadius, double yRadius) = 0;
	virtual void FillEllipse(const Point& center, double xRadius, double yRadius, RGBAColor color) = 0;

	virtual ~ICanvas() = default;
};
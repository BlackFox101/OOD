#pragma once
#include "Color.h"
#include "Point.h"
#include <iostream>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& from, int xRadius, int yRadius) = 0;
};

class SVGCanvas : public ICanvas
{
public:
	SVGCanvas(std::ostream& output);
	~SVGCanvas();

	void SetColor(Color color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& center, int xRadius, int yRadius) override;
private:
	std::ostream& m_output;
	Color m_color = Color::Black;
};
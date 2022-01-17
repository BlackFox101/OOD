#pragma once
#include "ICanvas.h"

class SVGCanvas : public ICanvas
{
public:
	SVGCanvas(std::ostream& output);
	~SVGCanvas();
	void SetLineColor(RGBAColor color);
	void SetLineWidth(double lineWidth);
	void DrawLine(const Point& from, const Point& to);
	void FillPoligon(const std::vector<Point>& points, RGBAColor color);
	void DrawEllipse(const Point& center, double xRadius, double yRadius);
	void FillEllipse(const Point& center, double xRadius, double yRadius, RGBAColor color);
private:
	std::ostream& m_output;
	RGBAColor m_color = 0x000000;
	double m_lineWidth = 5;

	static std::string ColorToString(const RGBAColor& color);
};


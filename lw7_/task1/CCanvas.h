#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
    CCanvas(std::ostream& output);
	void SetLineColor(RGBAColor color);
	void BeginFill(RGBAColor color);
	void EndFill();
	void MoveTo(Point p);
	void LineTo(Point p);
	void DrawEllipse(const Point& center, double xRadius, double yRadius);
private:
	std::ostream& m_output;
	RGBAColor m_lineColor = 0x000000;
	RGBAColor m_fillColor = 0x000000;
	bool isFill = false;
};


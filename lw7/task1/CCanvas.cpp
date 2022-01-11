#include "CCanvas.h"
#include "stdafx.h"

CCanvas::CCanvas(std::ostream& output)
    : m_output(output)
{
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
}

void CCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
	isFill = true;
	std::cout << "Start fiil" << std::endl;
}

void CCanvas::EndFill()
{
	isFill = false;
	std::cout << "End fiil" << std::endl;
}

void CCanvas::MoveTo(Point p)
{
	std::cout << "MoveTo " << p << std::endl;
}

void CCanvas::LineTo(Point p)
{
	std::cout << "LineTo " << p << std::endl;
}

void CCanvas::DrawEllipse(const Point& center, double xRadius, double yRadius)
{
	std::cout << "DrawEllipse center = " << center << ", xRadius = " << xRadius << ", yRadius = " << yRadius << std::endl;
}

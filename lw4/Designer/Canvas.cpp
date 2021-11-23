#include "Canvas.h"

SVGCanvas::SVGCanvas(std::ostream& output)
	: m_output(output)
{}

SVGCanvas::~SVGCanvas()
{
	m_output << "</svg>\n";
}

void SVGCanvas::SetColor(Color color)
{
	m_color = color;
}

void SVGCanvas::DrawLine(const Point& from, const Point& to)
{
	SetStartTag();
	m_output << "\t<line x1=\"" << from.x <<"\" y1=\"" << from.y << "\" x2=\"" << to.x << "\" y2=\"" << to.y << "\" stroke=\"" << m_color << "\" />\n";
}

void SVGCanvas::DrawEllipse(const Point& center, int xRadius, int yRadius)
{
	SetStartTag();
	m_output << "\t<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" rx=\"" << xRadius << "\" ry=\"" << yRadius << "\" style=\"fill:" << m_color << "\" />\n";
}

void SVGCanvas::SetStartTag() 
{
	if (m_isPictureStart)
	{
		m_isPictureStart = false;
		m_output << "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n";
	}
}
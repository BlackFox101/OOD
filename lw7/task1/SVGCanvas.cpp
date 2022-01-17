#include "SVGCanvas.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/format.hpp>

std::string SVGCanvas::ColorToString(const RGBAColor& color)
{
	std::ostringstream ss;
	ss << "#" << std::setfill('0') << std::hex << std::setw(6) << color;

	std::string str = ss.str();
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}

SVGCanvas::SVGCanvas(std::ostream& output)
	: m_output(output)
{
	m_output << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500px\" height=\"700px\">\n";
}

SVGCanvas::~SVGCanvas()
{
	m_output << "</svg>\n";
}

void SVGCanvas::SetLineColor(RGBAColor color)
{
	m_color = color;
}

void SVGCanvas::SetLineWidth(double lineWidth)
{
	m_lineWidth = lineWidth;
}

void SVGCanvas::DrawLine(const Point& from, const Point& to)
{
	auto fmt = boost::format(R"(<line x1="%1%" y1="%2%" x2="%3%" y2="%4%" stroke="%5%" stroke-width="%6%" stroke-linecap="square" />)");

	m_output << fmt % from.x % from.y % to.x % to.y % ColorToString(m_color) % m_lineWidth << std::endl;
}

void SVGCanvas::FillPoligon(const std::vector<Point>& points, RGBAColor color)
{
	std::ostringstream ssPoints;
	for (auto& point : points)
	{
		ssPoints << point.x << "," << point.y << " ";
	}
	std::string strPoint = ssPoints.str();
	strPoint.pop_back();

	auto fmt = boost::format(R"(<polygon points="%1%" fill="%2%" />)");
	m_output << fmt % strPoint % ColorToString(color) << std::endl;
}

void SVGCanvas::DrawEllipse(const Point& center, double xRadius, double yRadius)
{
	auto fmt = boost::format(R"(<ellipse cx="%1%" cy="%2%" rx="%3%" ry="%4%" stroke="%5%" stroke-width="%6%" fill="none" />)");

	m_output << fmt % center.x % center.y % xRadius % yRadius % ColorToString(m_color) % m_lineWidth << std::endl;
}

void SVGCanvas::FillEllipse(const Point& center, double xRadius, double yRadius, RGBAColor color)
{
	auto fmt = boost::format(R"(<ellipse cx="%1%" cy="%2%" rx="%3%" ry="%4%" fill="%5%" />)");

	m_output << fmt % center.x % center.y % xRadius % yRadius % ColorToString(color) << std::endl;
}

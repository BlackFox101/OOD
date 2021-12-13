#pragma once
#include "Point.h"

Point::Point()
{ }

Point::Point(double x, double y)
	: x(x)
	, y(y)
{}

std::istream& operator>>(std::istream& stream, Point& point)
{
	stream >> point.x >> point.y;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
	return stream << "{" << point.x << ", " << point.y << "}";
}
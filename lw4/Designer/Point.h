#pragma once
#include <istream>

struct Point
{
	Point();
	Point(int x, int y);

	int x, y;
};

std::istream& operator>>(std::istream& stream, Point& point);

std::ostream& operator<< (std::ostream& os, const Point& point);
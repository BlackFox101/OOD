#pragma once
#include "stdafx.h"

template <typename T>
struct PointType
{
	T x;
	T y;
};

template <typename T>
struct Rect
{
	PointType<T> leftTop;
	T width;
	T height;

	PointType<T> GetRightBottom() const
	{
		return { leftTop.x + width, leftTop.y + height };
	}
};

typedef Rect<double> RectD;
typedef PointType<double> Point;
typedef uint32_t RGBAColor;

Point operator-(const Point& left, const Point& right)
{
	return { left.x - right.x, left.y - right.y };
}

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
	return stream << "{" << point.x << ", " << point.y << "}";
}
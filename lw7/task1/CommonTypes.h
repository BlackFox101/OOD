#pragma once
#include <cstdint>
#include <iostream>

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
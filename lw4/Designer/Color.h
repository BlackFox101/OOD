#pragma once
#include <iostream>

enum class Color
{
    Green,
    Red,
    Blue,
    Yellow,
    Pink,
    Black
};

std::ostream& operator<<(std::ostream& stream, const Color& color);

//std::istream& operator>>(std::istream& stream, Color& color);

Color GetColorFromString(std::string strColor);
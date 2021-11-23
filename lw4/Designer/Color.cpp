#include "Color.h"
#include <map>
#include <string>
#include <stdexcept>

Color GetColorFromString(std::string strColor)
{
    const std::map<std::string, Color> ColorStrings{
            { "green",	Color::Green },
            { "red",	Color::Red },
            { "blue",	Color::Blue },
            { "yellow", Color::Yellow },
            { "pink",	Color::Pink },
            { "black",	Color::Black }
    };

    if (ColorStrings.find(strColor) == ColorStrings.end())
    {
        throw std::invalid_argument("Invalid color");
    }

    return ColorStrings.at(strColor);
}

std::string ColorToString(Color color)
{
    switch (color)
    {
    case Color::Green:
        return "green";
    case Color::Red:
        return "red";
    case Color::Blue:
        return "blue";
    case Color::Yellow:
        return "yellow";
    case Color::Pink:
        return "pink";
    case Color::Black:
        return "black";
    default:
        return "Unknown color";
    }
}

std::ostream& operator<<(std::ostream& stream, const Color& color)
{
    return stream << ColorToString(color);
}
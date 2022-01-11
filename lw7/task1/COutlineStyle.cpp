#include "COutlineStyle.h"
#include "stdafx.h"

const RGBAColor BLACK = 0x000000;
const double DEFAULT_OUTLINE_WIDTH = 5;

COutlineStyle::COutlineStyle()
    : m_lineColor(BLACK)
    , m_lineWidth(DEFAULT_OUTLINE_WIDTH)
{
}

std::optional<RGBAColor> COutlineStyle::GetColor() const
{
    return m_lineColor;
}

void COutlineStyle::SetColor(RGBAColor color)
{
    m_lineColor = color;
}

std::optional<double> COutlineStyle::GetWidth() const
{
    return m_lineWidth;
}

void COutlineStyle::SetWidth(double width)
{
    if (width < 0)
    {
        throw std::invalid_argument("The width cannot be negative");
    }
    m_lineWidth = width;
}

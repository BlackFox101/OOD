#include "CFillStyle.h"

std::optional<RGBAColor> CFillStyle::GetColor() const
{
    return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
    m_color = color;
}

#include "CGroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(std::vector<std::shared_ptr<IShape>> shapes)
	: m_shapes(shapes)
{
}

std::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	for (auto& shape : m_shapes)
	{
		std::optional<RGBAColor> currentColor = shape->GetFillStyle().GetColor();
		if (!currentColor)
		{
			return std::nullopt;
		}
		if (!color)
		{
			color = currentColor;
		}
		else if (*color != *currentColor)
		{
			return std::nullopt;
		}
	}
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		shape->GetFillStyle().SetColor(color);
	}
}

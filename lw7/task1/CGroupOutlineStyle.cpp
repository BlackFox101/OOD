#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(std::vector<std::shared_ptr<IShape>> shapes)
	: m_shapes(shapes)
{
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	for (auto& shape : m_shapes)
	{
		std::optional<RGBAColor> currentColor = shape->GetOutlineStyle().GetColor();
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

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetColor(color);
	}
}

std::optional<double> CGroupOutlineStyle::GetWidth() const
{
	std::optional<double> width = std::nullopt;
	for (auto& shape : m_shapes)
	{
		std::optional<double> currentWidth = shape->GetOutlineStyle().GetWidth();
		if (!currentWidth)
		{
			return std::nullopt;
		}
		if (!width)
		{
			width = currentWidth;
		}
		else if (*width != *currentWidth)
		{
			return std::nullopt;
		}
	}
}

void CGroupOutlineStyle::SetWidth(double width)
{
	for (auto& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetWidth(width);
	}
}

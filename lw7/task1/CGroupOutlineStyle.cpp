#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(std::shared_ptr<IOutlineStyleEnumarator> outlineStyleEnumerator)
	: m_outlineStyleEnumerator(outlineStyleEnumerator)
{
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	m_outlineStyleEnumerator->EnumarateOutlineStyles([&color](std::shared_ptr<IStyle> style) 
	{
		std::optional<RGBAColor> currentColor = style->GetColor();
		if (!currentColor)
		{
			color = std::nullopt;
			return;
		}
		if (!color)
		{
			color = currentColor;
		}
		else if (*color != *currentColor)
		{
			color = std::nullopt;
			return;
		}
	});
	return color;
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_outlineStyleEnumerator->EnumarateOutlineStyles([color](std::shared_ptr<IOutlineStyle> style)
	{
		style->SetColor(color);
	});
}

std::optional<double> CGroupOutlineStyle::GetWidth() const
{
	std::optional<double> width = std::nullopt;
	m_outlineStyleEnumerator->EnumarateOutlineStyles([&width](std::shared_ptr<IOutlineStyle> style)
	{
		std::optional<double> currentWidth = style->GetWidth();
		if (!currentWidth)
		{
			width = std::nullopt;
			return;
		}
		if (!width)
		{
			width = currentWidth;
		}
		else if (*width != *currentWidth)
		{
			width = std::nullopt;
			return;
		}
	});
	return width;
}

void CGroupOutlineStyle::SetWidth(double width)
{
	m_outlineStyleEnumerator->EnumarateOutlineStyles([width](std::shared_ptr<IOutlineStyle> style)
	{
		style->SetWidth(width);
	});
}

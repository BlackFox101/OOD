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
			return false;
		}
		if (!color)
		{
			color = currentColor;
		}
		else if (*color != *currentColor)
		{
			color = std::nullopt;
			return false;
		}

		return true;
	});
	return color;
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_outlineStyleEnumerator->EnumarateOutlineStyles([color](std::shared_ptr<IOutlineStyle> style)
	{
		style->SetColor(color);
		return true;
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
			return false;
		}
		if (!width)
		{
			width = currentWidth;
		}
		else if (*width != *currentWidth)
		{
			width = std::nullopt;
			return false;
		}
		return true;
	});
	return width;
}

void CGroupOutlineStyle::SetWidth(double width)
{
	m_outlineStyleEnumerator->EnumarateOutlineStyles([width](std::shared_ptr<IOutlineStyle> style)
	{
		style->SetWidth(width);
		return true;
	});
}

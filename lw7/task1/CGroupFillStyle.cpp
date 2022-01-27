#include "CGroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(std::shared_ptr<IFillStyleEnumerator> fillStyleEnumerator)
	: m_fillStyleEnumerator(fillStyleEnumerator)
{
}

std::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	m_fillStyleEnumerator->EnumarateFillStyles([&color](std::shared_ptr<IStyle> style) 
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

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_fillStyleEnumerator->EnumarateFillStyles([color](std::shared_ptr<IStyle> style)
	{
		style->SetColor(color);
		return true;
	});
}
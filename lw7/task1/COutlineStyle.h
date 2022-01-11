#pragma once
#include "IOutlineStyle.h"
#include "stdafx.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle();
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	std::optional<double> GetWidth() const;
	void SetWidth(double width);
private:
	std::optional<double> m_lineWidth;
	std::optional<RGBAColor> m_lineColor;
};


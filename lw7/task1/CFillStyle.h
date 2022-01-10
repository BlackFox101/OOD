#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);
private:
	std::optional<RGBAColor> m_color = std::nullopt;
};


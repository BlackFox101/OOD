#pragma once
#include "IStyle.h"
#include "IShape.h"
#include "IFillStyleEnumerator.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(std::shared_ptr<IFillStyleEnumerator> fillStyleEnumerator);
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);
private:
	std::shared_ptr<IFillStyleEnumerator> m_fillStyleEnumerator;
};


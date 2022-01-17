#pragma once
#include "IOutlineStyle.h"
#include "IShape.h"
#include "IOutlineStyleEnumarator.h"

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(std::shared_ptr<IOutlineStyleEnumarator> outlineStyleEnumerator);

	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	std::optional<double> GetWidth() const;
	void SetWidth(double width);
private:
	std::shared_ptr<IOutlineStyleEnumarator> m_outlineStyleEnumerator;
};
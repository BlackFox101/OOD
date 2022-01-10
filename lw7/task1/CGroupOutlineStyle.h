#pragma once
#include "IOutlineStyle.h"
#include "IShape.h"
#include <vector>
#include <memory>

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(std::vector<std::shared_ptr<IShape>> shapes);
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	std::optional<double> GetWidth() const;
	void SetWidth(double width);
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


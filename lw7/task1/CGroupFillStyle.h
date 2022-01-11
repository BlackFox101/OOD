#pragma once
#include "IStyle.h"
#include "IShape.h"
#include "stdafx.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>> shapes);
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


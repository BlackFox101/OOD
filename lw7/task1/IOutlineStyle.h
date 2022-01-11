#pragma once
#include "IStyle.h"
#include "stdafx.h"

class IOutlineStyle : public IStyle
{
public:
	virtual std::optional<double> GetWidth() const = 0;
	virtual void SetWidth(double width) = 0;
};
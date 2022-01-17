#pragma once
#include "stdafx.h"
#include "CommonTypes.h"

class IStyle
{
public:
	virtual std::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IStyle() = default;
};
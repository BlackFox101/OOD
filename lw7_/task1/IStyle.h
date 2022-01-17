#pragma once
#include "CommonTypes.h"
#include "stdafx.h"

class IStyle
{
public:
	virtual std::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IStyle() = default;
};
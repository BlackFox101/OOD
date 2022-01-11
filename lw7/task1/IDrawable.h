#pragma once
#include "ICanvas.h"
#include "stdafx.h"

class IDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;

	virtual ~IDrawable() = default;
};
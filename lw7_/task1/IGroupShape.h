#pragma once
#include "IShape.h"
#include "IShapes.h"
#include "stdafx.h"

class IGroupShape : public IShape, public IShapes
{
public:
	virtual ~IGroupShape() = default;
};
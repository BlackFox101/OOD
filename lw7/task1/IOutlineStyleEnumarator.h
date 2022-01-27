#pragma once
#include "stdafx.h"
#include "IOutlineStyle.h"

typedef std::function<bool(std::shared_ptr<IOutlineStyle>)> OutlineStyleCallback;

class IOutlineStyleEnumarator
{
public:
	virtual void EnumarateOutlineStyles(OutlineStyleCallback callback) const = 0;
	virtual ~IOutlineStyleEnumarator() = default;
};


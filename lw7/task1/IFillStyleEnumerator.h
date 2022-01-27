#pragma once
#include "stdafx.h"
#include "IStyle.h"

typedef std::function<bool(std::shared_ptr<IStyle>)> FillStyleCallback;

class IFillStyleEnumerator
{
public:
	virtual void EnumarateFillStyles(FillStyleCallback callback) const = 0;
	virtual ~IFillStyleEnumerator() = default;
};


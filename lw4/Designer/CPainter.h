#pragma once
#include "CPictureDraft.h"

class IPainter
{
public:
	virtual ~IPainter() = default;
	virtual void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const = 0;
};

class CPainter : public IPainter
{
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const override;
};

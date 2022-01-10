#pragma once
#include "IShape.h"
#include "IOutlineStyle.h"

class CShape : public IShape
{
public:
	RectD GetFrame() = 0;
	void SetFrame(const RectD& rect) = 0;

	IOutlineStyle& GetOutlineStyle();
	const IOutlineStyle& GetOutlineStyle() const;

	IStyle& GetFillStyle();
	const IStyle& GetFillStyle() const;

	std::shared_ptr<IGroupShape> GetGroup();
	std::shared_ptr<const IGroupShape> GetGroup() const;
private:
	std::shared_ptr<IGroupShape> m_parent;
};


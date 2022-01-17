#include "CShape.h"

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

void CShape::SetParent(std::shared_ptr<const IGroupShape> parent)
{
	m_parent = parent;
}

std::shared_ptr<const IGroupShape> CShape::GetParent() const
{
	return m_parent;
}

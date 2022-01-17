#include "CSlide.h"
#include "stdafx.h"

CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position >= m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::invalid_argument("There is no element for this index");
	}
	m_shapes.erase(m_shapes.begin() + index);
}

void CSlide::SetBackGroundColor(RGBAColor color)
{
	m_color = color;
}

std::optional<RGBAColor> CSlide::GetBackGroundColor() const
{
	return m_color;
}

#include "CGroupShape.h"
#include "stdafx.h"

CGroupShape::CGroupShape(std::shared_ptr<IShape> shape)
{
	m_shapes.push_back(shape);
}

RectD CGroupShape::GetFrame()
{
	Point leftTop;
	Point rightBottom;
	for (auto& shape : m_shapes)
	{
		RectD curFrame = shape->GetFrame();
		Point curLeftTop = curFrame.leftTop;
		Point curRightBottom = curFrame.GetRightBottom();
		leftTop.x = std::min(leftTop.x, curLeftTop.x);
		leftTop.y = std::min(leftTop.y, curLeftTop.y);
		rightBottom.x = std::max(rightBottom.x, curRightBottom.x);
		rightBottom.y = std::max(rightBottom.y, curRightBottom.y);

	}
	RectD frame;
	frame.leftTop = leftTop;
	frame.width = rightBottom.x - leftTop.x;
	frame.height = rightBottom.y - leftTop.y;
	return frame;
}

void CGroupShape::SetFrame(const RectD& rect)
{
	RectD groupFrame = GetFrame();
	double widthCoef = rect.width / groupFrame.width;
	double heightCoef = rect.height / groupFrame.height;

	for (auto& shape : m_shapes)
	{
		RectD shapeFrame = shape->GetFrame();
		Point vectorRelativeGroupFrameToShapeFrame = groupFrame.leftTop - shapeFrame.leftTop;
		RectD newFrame;
		newFrame.leftTop.x = shapeFrame.leftTop.x + vectorRelativeGroupFrameToShapeFrame.x * widthCoef;
		newFrame.leftTop.y = shapeFrame.leftTop.y + vectorRelativeGroupFrameToShapeFrame.y * heightCoef;
		newFrame.width = shapeFrame.width * widthCoef;
		newFrame.height = shapeFrame.height * heightCoef;
		shape->SetFrame(newFrame);
	}
}

std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()
{
	return m_outlineStyle ? m_outlineStyle : std::make_shared<CGroupOutlineStyle>(m_shapes);
}

std::shared_ptr<const IOutlineStyle> CGroupShape::GetOutlineStyle() const
{
	return m_outlineStyle ? m_outlineStyle : std::make_shared<CGroupOutlineStyle>(m_shapes);
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()
{
	return m_fillStyle ? m_fillStyle : std::make_shared<CGroupFillStyle>(m_shapes);
}

std::shared_ptr<const IStyle> CGroupShape::GetFillStyle() const
{
	return m_fillStyle ? m_fillStyle : std::make_shared<CGroupFillStyle>(m_shapes);
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (!CanInsertShape(shape))
	{
		throw std::logic_error("This shape has already been inserted");
	}

	if (position >= m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	auto shape = m_shapes.at(index);
	auto parent = shape->GetParent();
	if (!parent && m_shapes.size() == 1)
	{
		throw std::logic_error("The last element of the group cannot be deleted");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void CGroupShape::SetParent(std::shared_ptr<const IGroupShape> parent)
{
	m_parent = parent;
}

std::shared_ptr<const IGroupShape> CGroupShape::GetParent() const
{
	return m_parent;
}

void CGroupShape::Draw(ICanvas& canvas)
{
}

bool CGroupShape::CanInsertShape(const std::shared_ptr<IShape>& shape) const
{
	auto currentShape = GetGroup();
	while (currentShape)
	{
		if (currentShape == shape)
		{
			return false;
		}
		currentShape = currentShape->GetParent();
	}
	return true;
}
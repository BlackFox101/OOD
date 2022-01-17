#include "CGroupShape.h"
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"

CGroupShape::CGroupShape(std::shared_ptr<IShape> shape/*, CreateTag*/)
{
	m_shapes.push_back(shape);
	// TODO: добавить первому элементу родител€ - эту группу
	// сразу добавить нельз€ т.к shared_ptr еще не создалс€
}

/*std::shared_ptr<IGroupShape> CGroupShape::Create(std::shared_ptr<IShape> shape)
{
	return std::make_shared<CGroupShape>(shape);
}*/

RectD CGroupShape::GetFrame()
{
	auto firstShapeFrame = m_shapes.at(0)->GetFrame();
	Point leftTop = firstShapeFrame.leftTop;
	Point rightBottom = firstShapeFrame.GetRightBottom();
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

namespace
{
	Point operator-(const Point& left, const Point& right)
	{
		return { left.x - right.x, left.y - right.y };
	}
}

void CGroupShape::SetFrame(const RectD& rect)
{
	RectD groupFrame = GetFrame();
	double widthCoef = rect.width / groupFrame.width;
	double heightCoef = rect.height / groupFrame.height;

	for (auto shape : m_shapes)
	{
		RectD shapeFrame = shape->GetFrame();
		Point vectorRelativeGroupFrameToShapeFrame = shapeFrame.leftTop - groupFrame.leftTop;

		RectD newFrame;
		newFrame.leftTop.x = rect.leftTop.x + vectorRelativeGroupFrameToShapeFrame.x * widthCoef;
		newFrame.leftTop.y = rect.leftTop.y + vectorRelativeGroupFrameToShapeFrame.y * heightCoef;
		newFrame.width = shapeFrame.width * widthCoef;
		newFrame.height = shapeFrame.height * heightCoef;

		shape->SetFrame(newFrame);
	}
}

std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()
{
	if (m_outlineStyle)
	{
		return m_outlineStyle;
	}
	m_outlineStyle = std::make_shared<CGroupOutlineStyle>(shared_from_this());

	return m_outlineStyle;
}

std::shared_ptr<const IOutlineStyle> CGroupShape::GetOutlineStyle() const
{
	return GetOutlineStyle();
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()
{
	if (m_fillStyle)
	{
		return m_fillStyle;
	}
	m_fillStyle = std::make_shared<CGroupFillStyle>(shared_from_this());

	return m_fillStyle;
}

std::shared_ptr<const IStyle> CGroupShape::GetFillStyle() const
{
	return GetFillStyle();
}

// TODO: —оздание экземпл€ра объекта через статический метод 
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
	if (IsExistShape(shape) || !CanInsertShape(shape))
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
	shape->SetParent(GetGroup());
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{

	return m_shapes.at(index);
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

void CGroupShape::SetParent(std::shared_ptr<const IGroupShape> parent)
{
	if (GetGroup() == parent)
	{
		throw std::logic_error("You cannot set yourself as a parent");
	}
	m_parent = parent;
	
}

std::shared_ptr<const IGroupShape> CGroupShape::GetParent() const
{
	return m_parent;
}

void CGroupShape::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CGroupShape::EnumarateFillStyles(FillStyleCallback callback) const
{
	for (auto& shape : m_shapes)
	{
		callback(shape->GetFillStyle());
	}
}

void CGroupShape::EnumarateOutlineStyles(OutlineStyleCallback callback) const
{
	for (auto& shape : m_shapes)
	{
		callback(shape->GetOutlineStyle());
	}
}

bool CGroupShape::CanInsertShape(std::shared_ptr<const IShape> shape) const
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

bool CGroupShape::IsExistShape(std::shared_ptr<const IShape> shape) const
{
	return std::find(m_shapes.begin(), m_shapes.end(), shape) != m_shapes.end();
}


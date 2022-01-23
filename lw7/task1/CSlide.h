#pragma once
#include "IShape.h"
#include <memory>

// TODO: ни где не используется интерфейс
class CSlide
{
public:
	CSlide(double width, double height);
	double GetWidth() const;
	double GetHeight() const;

	size_t GetShapesCount() const;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	void SetBackGroundColor(RGBAColor color);
	std::optional<RGBAColor> GetBackGroundColor() const;

	void Draw(ICanvas& canvas);

private:
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width, m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


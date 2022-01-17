#pragma once
#include "ISlide.h"

// TODO: ни где не используется интерфейс
class CSlide : public ISlide
{
public:
	CSlide(double width, double height);
	double GetWidth() const override;
	double GetHeight() const override;

	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

	void SetBackGroundColor(RGBAColor color) override;
	std::optional<RGBAColor> GetBackGroundColor() const override;

	void Draw(ICanvas& canvas) override;

private:
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width, m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


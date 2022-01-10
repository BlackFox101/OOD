#pragma once
#include "ISlide.h"
#include <vector>

class CSlide : public ISlide
{
public:
	CSlide(double width, double height);
	double GetWidth() const override;
	double GetHeight() const override;

	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void InsertShape(std::shared_ptr<IShape> shape, std::optional<size_t> position = std::nullopt) override;
	void RemoveShapeAtIndex(size_t index) override;

	void SetBackGroundColor(RGBAColor color) override;
	std::optional<RGBAColor> GetBackGroundColor() const override;

private:
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width, m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

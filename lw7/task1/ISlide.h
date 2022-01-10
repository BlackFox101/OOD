#pragma once
#include "IDrawable.h"
#include "IShapes.h"

class ISlide : public IDrawable
{
public:
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;

	virtual size_t GetShapesCount() const = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(std::shared_ptr<IShape> shape, std::optional<size_t> position) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual void SetBackGroundColor(RGBAColor color) = 0;
	virtual std::optional<RGBAColor> GetBackGroundColor() const = 0;

	virtual ~ISlide() = default;
};

#pragma once
#include <memory>
#include <sstream>
#include "CShape.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CRegularPolygon.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::shared_ptr<CShape> CreateShape(const std::string& description) = 0;
	virtual std::string GetShapesInfo() const = 0;
};

class CShapeFactory : public IShapeFactory
{
public:
	std::shared_ptr<CShape> CreateShape(const std::string& description) override;
	std::string GetShapesInfo() const override;

private:
	std::shared_ptr<CRectangle> CreateRectangle(std::stringstream& shapeDescription);
	std::shared_ptr<CTriangle> CreateTriangle(std::stringstream& shapeDescription);
	std::shared_ptr<CEllipse> CreateEllipse(std::stringstream& shapeDescription);
	std::shared_ptr<CRegularPolygon> CreateRegularPolygon(std::stringstream& shapeDescription);
};
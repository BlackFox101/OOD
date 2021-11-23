#include "CShapeFactory.h"
#include <string>
#include <map>

using namespace std;

const string RECTANGLE = "rectangle";
const string TRIANGLE = "triangle";
const string ELLIPSE = "ellipse";
const string REGULAR_POLYGON = "regularPolygon";

const map<string, string> ShapesInfo 
{
	{ RECTANGLE,		"Format: rectangle <x1> <y1> <x2> <y2> <color>\n" },
	{ TRIANGLE,			"Format: triangle <x1> <y1> <x2> <y2> <x3> <y3> <color>\n" },
	{ ELLIPSE,			"Format: ellipse <x> <y> <horizontalRadius> <verticalRadius> <color>\n" },
	{ REGULAR_POLYGON,	"Format: regularPolygon <vertexCount> <x> <y> <radius> <color>\n" },
};

shared_ptr<CRectangle> CShapeFactory::CreateRectangle(std::stringstream& shapeDescription)
{
	string colorStr;
	int x1, x2, y1, y2;
	shapeDescription >> x1 >> y1 >> x2 >> y2 >> colorStr;
	if (shapeDescription.fail())
	{
		throw invalid_argument(ShapesInfo.at(RECTANGLE));
	}
	Color color = GetColorFromString(colorStr);

	Point leftTop(min(x1, x2), max(y1, y2));
	Point rightBottom(max(x1, x2), min(y1, y2));

	return make_shared<CRectangle>(color, leftTop, rightBottom);
}

shared_ptr<CTriangle> CShapeFactory::CreateTriangle(std::stringstream& shapeDescription)
{
	string colorStr;
	Point a, b, c;
	shapeDescription >> a >> b >> c >> colorStr;
	if (shapeDescription.fail())
	{
		throw invalid_argument(ShapesInfo.at(TRIANGLE));
	}
	Color color = GetColorFromString(colorStr);

	return make_shared<CTriangle>(color, a, b, c);
}

shared_ptr<CEllipse> CShapeFactory::CreateEllipse(std::stringstream& shapeDescription)
{
	string colorStr;
	Point center;
	int xRadius, yRadius;
	shapeDescription >> center >> xRadius >> yRadius >> colorStr;
	if (shapeDescription.fail())
	{
		throw invalid_argument(ShapesInfo.at(ELLIPSE));
	}
	Color color = GetColorFromString(colorStr);

	return make_shared<CEllipse>(color, center, xRadius, yRadius);
}

shared_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::stringstream& shapeDescription)
{
	string colorStr;
	int vertexCount;
	Point center;
	int radius;
	shapeDescription >> vertexCount >> center >> radius >> colorStr;
	if (shapeDescription.fail())
	{
		throw invalid_argument(ShapesInfo.at(REGULAR_POLYGON));
	}
	Color color = GetColorFromString(colorStr);

	return make_shared<CRegularPolygon>(color, vertexCount, center, radius);
}

shared_ptr<CShape> CShapeFactory::CreateShape(const string& description)
{
	stringstream shapeDescription(description);

	string shapeName;
	shapeDescription >> shapeName;

	if (shapeName == RECTANGLE)
	{
		return CreateRectangle(shapeDescription);
	}
	else if (shapeName == TRIANGLE)
	{
		return CreateTriangle(shapeDescription);
	}
	else if (shapeName == ELLIPSE)
	{
		return CreateEllipse(shapeDescription);
	}
	else if (shapeName == REGULAR_POLYGON)
	{
		return CreateRegularPolygon(shapeDescription);
	}

	throw invalid_argument("Unknown figure");
}

string CShapeFactory::GetShapesInfo() const
{
	string info;
	for (auto shape : ShapesInfo)
	{
		string shapeName = shape.first;
		shapeName[0] = toupper(shapeName[0]);
		info += shapeName + ".\t" + shape.second;
	}
	return info;
}

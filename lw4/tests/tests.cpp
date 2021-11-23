#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../Designer/CShapeFactory.h"
#include "../Designer/CDesigner.h"
#include "../Designer/CPainter.h"

using namespace std;

bool operator==(const Point& left, const Point& right)
{
	return left.x == right.x && left.y == right.y;
}

/*TEST_CASE("Create Color")
{
	WHEN("Read color from string")
	{
		Color color;
		THEN("Green")
		{
			color = GetColorFromString("green");
			REQUIRE(color == Color::Green);
		}
		THEN("Red")
		{
			color = GetColorFromString("red");
			REQUIRE(color == Color::Red);
		}
		THEN("Blue")
		{
			color = GetColorFromString("blue");
			REQUIRE(color == Color::Blue);
		}
		THEN("Yellow")
		{
			color = GetColorFromString("yellow");
			REQUIRE(color == Color::Yellow);
		}
		THEN("Pink")
		{
			color = GetColorFromString("pink");
			REQUIRE(color == Color::Pink);
		}
		THEN("Black")
		{
			color = GetColorFromString("black");
			REQUIRE(color == Color::Black);
		}
		THEN("Unknown")
		{
			CHECK_THROWS(GetColorFromString("blackk"));
		}
	}
	WHEN("Write color to output")
	{
		THEN("Green")
		{
			Color color = Color::Green;
			ostringstream output;
			output << color;
			CHECK(output.str() == "green");
		}
		THEN("Red")
		{
			Color color = Color::Red;
			ostringstream output;
			output << color;
			CHECK(output.str() == "red");
		}
		THEN("Blue")
		{
			Color color = Color::Blue;
			ostringstream output;
			output << color;
			CHECK(output.str() == "blue");
		}
		THEN("Yellow")
		{
			Color color = Color::Yellow;
			ostringstream output;
			output << color;
			CHECK(output.str() == "yellow");
		}
		THEN("Pink")
		{
			Color color = Color::Pink;
			ostringstream output;
			output << color;
			CHECK(output.str() == "pink");
		}
		THEN("Black")
		{
			Color color = Color::Black;
			ostringstream output;
			output << color;
			CHECK(output.str() == "black");
		}
	}
}

TEST_CASE("Create shapes")
{
	WHEN("Create Rectangle")
	{
		//Rectangle format: <x1> <y1> <x2> <y2> <color>
		CShapeFactory shapeFactory;
		THEN("Ok")
		{
			auto shape = shapeFactory.CreateShape("rectangle 0 0 10 15 green");
			CRectangle& rectangle = dynamic_cast<CRectangle &>(*shape);
			CHECK(rectangle.GetLeftTop() == Point(0, 10));
			CHECK(rectangle.GetRightBottom() == Point(0, 15));
			CHECK(rectangle.GetColor() == Color::Green);

			shape = shapeFactory.CreateShape("triangle 5 5 0 0 -3 -3 black");
			CTriangle& triangle = dynamic_cast<CTriangle&>(*shape);
			CHECK(triangle.GetVertex1() == Point(5, 5));
			CHECK(triangle.GetVertex2() == Point(0, 0));
			CHECK(triangle.GetVertex3() == Point(-3, -3));
			CHECK(triangle.GetColor() == Color::Black);

			shape = shapeFactory.CreateShape("ellipse 0 0 5 10 blue");
			CEllipse& ellipse = dynamic_cast<CEllipse&>(*shape);
			CHECK(ellipse.GetCenter() == Point(0, 0));
			CHECK(ellipse.GetHorizontalRadius() == 5);
			CHECK(ellipse.GetVerticalRadius() == 10);
			CHECK(ellipse.GetColor() == Color::Blue);

			shape = shapeFactory.CreateShape("regularPolygon 5 0 0 5 pink");
			CRegularPolygon& regularPolygon = dynamic_cast<CRegularPolygon&>(*shape);
			CHECK(regularPolygon.GetVertexCount() == 5);
			CHECK(regularPolygon.GetCenter() == Point(0, 0));
			CHECK(regularPolygon.GetRadius() == 5);
			CHECK(regularPolygon.GetColor() == Color::Pink);
		}
		THEN("Invalid format")
		{
			CHECK_THROWS(shapeFactory.CreateShape("rectangle 0  10 15 green"));

			CHECK_THROWS(shapeFactory.CreateShape("triangle 5 5 0  -3 -3 black"));

			CHECK_THROWS(shapeFactory.CreateShape("ellipse 0 0  10 blue"));

			CHECK_THROWS(shapeFactory.CreateShape("regularPolygon 5 0 5 pink"));
		}
	}
}

TEST_CASE("SVG Canvas")
{
	WHEN("SetColor")
	{
		ostringstream output;
		{
			SVGCanvas canvas(output);
			canvas.SetColor(Color::Green);
			canvas.DrawLine(Point(0, 0), Point(100, 100));
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
			"\t<line x1=\"0\" y1=\"0\" x2=\"100\" y2=\"100\" stroke=\"green\" />\n"
			"</svg>\n");
	}

	WHEN("DrawLine")
	{
		ostringstream output;
		{
			SVGCanvas canvas(output);
			canvas.DrawLine(Point(0, 0), Point(100, 100));
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
			"\t<line x1=\"0\" y1=\"0\" x2=\"100\" y2=\"100\" stroke=\"black\" />\n"                                                          
			"</svg>\n");
	}
	WHEN("DrawEllipse")
	{
		ostringstream output;
		{
			SVGCanvas canvas(output);
			canvas.DrawEllipse(Point(100, 100), 50, 50);
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
			"\t<ellipse cx=\"100\" cy=\"100\" rx=\"50\" ry=\"50\" />\n"
			"</svg>\n");
	}
}*/

TEST_CASE("Draw shapes")
{
	WHEN("Draw rectangle")
	{
		ostringstream output;
		string line = "rectangle 0 10 20 0 black";
		{
			CShapeFactory shapeFactory;
			CDesigner designer(shapeFactory);
			SVGCanvas canvas(output);

			auto shape = shapeFactory.CreateShape(line);
			shape->Draw(canvas);
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
			"\t<line x1=\"0\" y1=\"0\" x2=\"20\" y2=\"0\" stroke=\"black\" />\n"
			"\t<line x1=\"20\" y1=\"0\" x2=\"20\" y2=\"10\" stroke=\"black\" />\n"
			"\t<line x1=\"20\" y1=\"10\" x2=\"0\" y2=\"10\" stroke=\"black\" />\n"
			"\t<line x1=\"0\" y1=\"10\" x2=\"0\" y2=\"0\" stroke=\"black\" />\n"
			"</svg>\n");
	}
	WHEN("Draw triangle")
	{
		ostringstream output;
		string line = "triangle 0 0 5 5 0 10 black";
		{
			CShapeFactory shapeFactory;
			CDesigner designer(shapeFactory);
			SVGCanvas canvas(output);

			auto shape = shapeFactory.CreateShape(line);
			shape->Draw(canvas);
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
				"\t<line x1=\"0\" y1=\"0\" x2=\"5\" y2=\"5\" stroke=\"black\" />\n"
				"\t<line x1=\"5\" y1=\"5\" x2=\"0\" y2=\"10\" stroke=\"black\" />\n"
				"\t<line x1=\"0\" y1=\"10\" x2=\"0\" y2=\"0\" stroke=\"black\" />\n"
			"</svg>\n");
	}
	WHEN("Draw ellipse")
	{
		ostringstream output;
		string line = "ellipse 10 10 5 5 black";
		{
			CShapeFactory shapeFactory;
			CDesigner designer(shapeFactory);
			SVGCanvas canvas(output);

			auto shape = shapeFactory.CreateShape(line);
			shape->Draw(canvas);
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
				"\t<ellipse cx=\"10\" cy=\"10\" rx=\"5\" ry=\"5\" style=\"fill:black\" />\n"
			"</svg>\n");
	}
	WHEN("Draw Regular polygon")
	{
		ostringstream output;
		string line = "regularPolygon 4 100 100 30 blue";
		{
			CShapeFactory shapeFactory;
			CDesigner designer(shapeFactory);
			SVGCanvas canvas(output);

			auto shape = shapeFactory.CreateShape(line);
			shape->Draw(canvas);
		}
		CHECK(output.str() == "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1500px\" height = \"700px\">\n"
				"\t<line x1=\"70\" y1=\"70\" x2=\"130\" y2=\"70\" stroke=\"black\" />\n"
				"\t<line x1=\"130\" y1=\"70\" x2=\"130\" y2=\"130\" stroke=\"black\" />\n"
				"\t<line x1=\"130\" y1=\"130\" x2=\"70\" y2=\"130\" stroke=\"black\" />\n"
				"\t<line x1=\"70\" y1=\"130\" x2=\"70\" y2=\"70\" stroke=\"black\" />\n"
			"</svg>\n");
	}
}
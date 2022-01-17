#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../task1/SVGCanvas.h"
#include "../task1/CRectangle.h"
#include "../task1/CTriangle.h"
#include "../task1/CEllipse.h"
#include "../task1/CGroupShape.h"

using namespace std;

bool operator==(const RectD& left, const RectD& right)
{
	return left.leftTop.x == right.leftTop.x
		&& left.leftTop.y == right.leftTop.y
		&& left.width == right.width
		&& left.height == right.height;
}

bool operator==(const Point& left, const Point& right)
{
	return left.x == right.x
		&& left.y == right.y;
}

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
	return stream << point.x << ", " << point.y ;
}

std::ostream& operator<<(std::ostream& stream, const RectD& rect)
{
	return stream << rect.leftTop << endl
		<< "width: " << rect.width << endl
		<< "height: " << rect.height << endl;
}

TEST_CASE("SVGCanvas drawing")
{
	ostringstream output;
	SVGCanvas canvas(output);
	WHEN("DrawLine test")
	{
		canvas.DrawLine({ 0, 2 }, { 10, 15 });
		THEN("DrawLine success")
		{
			CHECK(output.str() == "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500px\" height=\"700px\">\n"
				"<line x1=\"0\" y1=\"2\" x2=\"10\" y2=\"15\" stroke=\"#000000\" stroke-width=\"5\" stroke-linecap=\"square\" />\n"
			);
		}
	}

	WHEN("DrawEllipse")
	{
		canvas.DrawEllipse({ 150, 100 }, 100, 50);
		THEN("DrawEllipse success")
		{
			CHECK(output.str() == "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500px\" height=\"700px\">\n"
				"<ellipse cx=\"150\" cy=\"100\" rx=\"100\" ry=\"50\" stroke=\"#000000\" stroke-width=\"5\" fill=\"none\" />\n"
			);
		}
	}

	WHEN("FillEllipse")
	{
		canvas.FillEllipse({ 150, 100 }, 100, 50, 0x0000FF);
		THEN("FillEllipse success")
		{
			CHECK(output.str() == "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500px\" height=\"700px\">\n"
				"<ellipse cx=\"150\" cy=\"100\" rx=\"100\" ry=\"50\" fill=\"#0000FF\" />\n"
			);
		}
	}

	WHEN("FillPoligon")
	{
		std::vector<Point> points;
		points.push_back({ 10, 10 });
		points.push_back({ 30, 10 });
		points.push_back({ 30, 20 });
		points.push_back({ 10, 20 });
		canvas.FillPoligon(points, 0x0000FF);
		THEN("FillPoligon success")
		{
			CHECK(output.str() == "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500px\" height=\"700px\">\n"
				"<polygon points=\"10,10 30,10 30,20 10,20\" fill=\"#0000FF\" />\n"
			);
		}
	}
}

TEST_CASE("SetFrame")
{
	WHEN("CRectangle")
	{
		CRectangle rectangle(Point{ 100, 100 }, Point{ 300, 200 });
		CHECK(rectangle.GetFrame() == RectD{ Point{ 100, 100 }, 200, 100 });
		THEN("New frame success")
		{
			RectD newFrame = RectD{ Point{ 100, 100 }, 100, 100 };
			rectangle.SetFrame(newFrame);
			CHECK(rectangle.GetFrame() == newFrame);
		}
	}
	WHEN("CTriangle")
	{
		CTriangle triangle(Point{ 100, 100 }, Point{ 300, 100 }, Point{ 200, 50 });
		CHECK(triangle.GetFrame() == RectD{ Point{ 100, 50 }, 200, 50 });
		THEN("New frame success1")
		{
			RectD newFrame = RectD{ Point{ 100, 50 }, 100, 100 };
			triangle.SetFrame(newFrame);
			CHECK(triangle.GetVertex1() == Point{ 100, 150 });
			CHECK(triangle.GetVertex2() == Point{ 200, 150 });
			CHECK(triangle.GetVertex3() == Point{ 150, 50 });
			CHECK(triangle.GetFrame() == newFrame);
		}
	}

	WHEN("CEllipse")
	{
		CEllipse ellipse(Point{ 100, 100 }, 100, 50);
		CHECK(ellipse.GetFrame() == RectD{ Point{ 0, 50 }, 200, 100 });
		THEN("New frame success")
		{
			RectD newFrame = RectD{ Point{ 50, 50 }, 100, 50 };
			ellipse.SetFrame(newFrame);
			CHECK(ellipse.GetFrame() == newFrame);
		}
	}
}

TEST_CASE("CGroupShape")
{
	shared_ptr<IShape> foundation = make_shared<CRectangle>(Point{ 100, 100 }, Point{ 300, 200 });
	shared_ptr<IShape> tube = make_shared<CRectangle>(Point{ 270, 50 }, Point{ 290, 100 });
	shared_ptr<IShape> roof = make_shared<CTriangle>(Point{ 100, 100 }, Point{ 300, 100 }, Point{ 200, 50 });
	shared_ptr<IShape> sun = make_shared<CEllipse>(Point{ 0, 0 }, 30, 30);

	shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
	group->InsertShape(tube);
	group->InsertShape(roof);
	group->InsertShape(sun);
	REQUIRE(group->GetShapesCount() == 4);

	WHEN("GetOutlineStyle")
	{
		auto outlineStyle = group->GetOutlineStyle();
		THEN("New color equal")
		{
			outlineStyle->SetColor(0xFFFFFF);
			for (size_t i = 0; i < group->GetShapesCount(); i++)
			{
				auto shape = group->GetShapeAtIndex(i);
				auto color = shape->GetOutlineStyle()->GetColor();
				REQUIRE(color == 0xFFFFFF);
			}
		}
		THEN("New width equal")
		{
			outlineStyle->SetWidth(13);
			for (size_t i = 0; i < group->GetShapesCount(); i++)
			{
				auto shape = group->GetShapeAtIndex(i);
				auto color = shape->GetOutlineStyle()->GetWidth();
				REQUIRE(color == 13);
			}
		}
	}

	WHEN("GetFillStyle")
	{
		auto outlineStyle = group->GetFillStyle();
		THEN("New color equal")
		{
			outlineStyle->SetColor(0xFFFFFF);
			for (size_t i = 0; i < group->GetShapesCount(); i++)
			{
				auto shape = group->GetShapeAtIndex(i);
				auto color = shape->GetFillStyle()->GetColor();
				REQUIRE(color == 0xFFFFFF);
			}
		}
	}

	WHEN("GetGroup")
	{
		CHECK(group == group->GetGroup());
	}

	WHEN("InsertShape")
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
		THEN("isnert new shape")
		{
			shared_ptr<IShape> shape = make_shared<CEllipse>(Point{ 0, 0 }, 30, 30);
			CHECK_NOTHROW(group->InsertShape(shape));
		}
		THEN("isnert exist elemet")
		{
			CHECK_THROWS(group->InsertShape(foundation));
		}
	}

	WHEN("GetShapeAtIndex")
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
		CHECK(foundation == group->GetShapeAtIndex(0));
	}

	WHEN("SetParent")
	{
		THEN("SetParent youself")
		{
			shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
			shared_ptr<IShape> sun = make_shared<CEllipse>(Point{ 0, 0 }, 30, 30);
			CHECK_THROWS(group->SetParent(group));
		}
		THEN("SetParent new group")
		{
			shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
			shared_ptr<IShape> sun = make_shared<CEllipse>(Point{ 0, 0 }, 30, 30);
			shared_ptr<CGroupShape> newGroup = make_shared<CGroupShape>(sun);
			group->SetParent(newGroup);
			CHECK(group->GetParent() == newGroup);
		}
	}

	WHEN("GetParent")
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
		THEN("With New group -> nullptr")
		{
			CHECK(group->GetParent() == nullptr);
		}
	}

	WHEN("RemoveShapeAtIndex")
	{
		THEN("Remove last shape")
		{
			shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
			REQUIRE(group->GetShapesCount() == 1);
			CHECK_THROWS(group->RemoveShapeAtIndex(0));
		}
		THEN("Remove not last shape")
		{
			shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
			group->InsertShape(tube);
			REQUIRE(group->GetShapesCount() == 2);
			CHECK_NOTHROW(group->RemoveShapeAtIndex(0));
			REQUIRE(group->GetShapesCount() == 1);
		}
	}

	WHEN("GetFrame")
	{
		CHECK(group->GetFrame() == RectD{ Point{ -30, -30 }, 330, 230 });
	}

	WHEN("GetFrame")
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
		CHECK(group->GetFrame() == RectD{ Point{ 100, 100 }, 200, 100 });
		group->SetFrame(RectD{ Point{ 100, 100 }, 100, 100 });
		CHECK(group->GetFrame() == RectD{ Point{ 100, 100 }, 100, 100 });
	}

	// TODO: добавить тест
	// Взяли стили  поменяли у группы что-то(добавили красную фигуру), цвет должен быть как смешанный
	WHEN("A new figure has been added to the group")
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>(foundation);
		group->InsertShape(tube);
		auto outlineStyle = group->GetOutlineStyle();
		outlineStyle->SetColor(0xFF00FF);
		REQUIRE(outlineStyle->GetColor() == 0xFF00FF);
		THEN("Got a mixed color")
		{
			shared_ptr<IShape> sun = make_shared<CEllipse>(Point{ 0, 0 }, 30, 30);
			sun->GetOutlineStyle()->SetColor(0x00FF00);

			group->InsertShape(sun);
			REQUIRE(outlineStyle->GetColor() == nullopt);
		}
	}
}
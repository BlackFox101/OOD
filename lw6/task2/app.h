#pragma once
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"
#include "ModernGraphicsAdapter.h"

// ѕространство имен приложени€ (доступно дл€ модификации)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		//modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		//(void)&renderer; // устран€ем предупреждение о неиспользуемой переменной

		ModernGraphicsLibAdapter adapter(cout);
		shape_drawing_lib::CCanvasPainter painter(adapter);
		PaintPicture(painter);
	}

}
#pragma once
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"
#include "ModernGraphicsAdapter.h"

// ������������ ���� ���������� (�������� ��� �����������)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x00FF00);
		CRectangle rectangle({ 30, 40 }, 18, 24, 0x00FFAA);

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
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		(void)&renderer; // ��������� �������������� � �������������� ����������

		ModernGraphicsLibAdapter adapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(adapter);
		PaintPicture(painter);
	}

}
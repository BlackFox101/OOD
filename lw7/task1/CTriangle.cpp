#include "CTriangle.h"
#include "stdafx.h"

CTriangle::CTriangle(Point vertex1, Point vertex2, Point vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

RectD CTriangle::GetFrame()
{
	double leftX = std::min(m_vertex1.x, m_vertex2.x, m_vertex3.x);
	double rightX = std::max(m_vertex1.x, m_vertex2.x, m_vertex3.x);
	double topY = std::min(m_vertex1.y, m_vertex2.y, m_vertex3.y);
	double bottomY = std::max(m_vertex1.y, m_vertex2.y, m_vertex3.y);

	RectD frame;
	frame.leftTop = { leftX, topY };
	frame.width = rightX - leftX;
	frame.height = bottomY - topY;

	return frame;
}

void CTriangle::SetFrame(const RectD& rect)
{
	auto currentFrame = GetFrame();
	double widthCoef = rect.width / currentFrame.width;
	double heightCoef = rect.height / currentFrame.height;

	for (auto vertex : { m_vertex1, m_vertex2, m_vertex3 })
	{
		Point vectorRelativeVertexToLeftTopFrame = vertex - currentFrame.leftTop;
		vertex.x = rect.leftTop.x + vectorRelativeVertexToLeftTopFrame.x * widthCoef;
		vertex.y = rect.leftTop.y + vectorRelativeVertexToLeftTopFrame.y * heightCoef;
	}
}

void CTriangle::Draw(ICanvas& canvas)
{
	auto outlineStyle = GetOutlineStyle();
	auto outlineColor = outlineStyle->GetColor();
	auto outlineWidth = outlineStyle->GetColor();
	if (outlineColor)
	{
		canvas.SetLineColor(*outlineColor);
	}
	if (outlineWidth)
	{
		canvas.SetLineWidth(*outlineWidth);
	}
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);

	auto fillColor = GetFillStyle()->GetColor();
	if (fillColor)
	{
		std::vector<Point> points = {
			   m_vertex1,
			   m_vertex2,
			   m_vertex3
		};
		canvas.FillPoligon(points, *fillColor);
	}
}

#include "CEllipse.h"

CEllipse::CEllipse(const Point& center, double xRadius, double yRadius)
	: m_center(center)
	, m_xRadius(xRadius)
	, m_yRadius(yRadius)
{
}

RectD CEllipse::GetFrame()
{
	RectD frame;
	frame.leftTop = { m_center.x - m_xRadius, m_center.y - m_yRadius };
	frame.width = m_xRadius + m_xRadius;
	frame.height = m_yRadius + m_yRadius;

	return frame;
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_center = { rect.leftTop.x + rect.width / 2, rect.leftTop.y + rect.height / 2 };
	m_xRadius = rect.width / 2;
	m_yRadius = rect.height / 2;
}

void CEllipse::Draw(ICanvas& canvas)
{
	auto outlineStyle = GetOutlineStyle();
	auto outlineColor = outlineStyle->GetColor();
	auto outlineWidth = outlineStyle->GetWidth();
	if (outlineColor)
	{
		canvas.SetLineColor(*outlineColor);
	}
	if (outlineWidth)
	{
		canvas.SetLineWidth(*outlineWidth);
	}
	canvas.DrawEllipse(m_center, m_xRadius, m_yRadius);

	auto fillColor = GetFillStyle()->GetColor();
	if (fillColor)
	{
		canvas.FillEllipse(m_center, m_xRadius, m_yRadius, *fillColor);
	}
}
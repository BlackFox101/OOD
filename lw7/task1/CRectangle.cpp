#include "CRectangle.h"

CRectangle::CRectangle(const Point& leftTop, const Point& rightBottom)
    : m_leftTop(leftTop)
    , m_rightBottom(rightBottom)
{
}

RectD CRectangle::GetFrame()
{
    RectD frame;
    frame.leftTop = m_leftTop;
    frame.width = m_rightBottom.x - m_leftTop.x;
    frame.height = m_rightBottom.y - m_leftTop.y;
    return frame;
}

void CRectangle::SetFrame(const RectD& rect)
{
    m_leftTop = rect.leftTop;
    m_rightBottom.x = m_leftTop.x + rect.width;
    m_rightBottom.y = m_leftTop.y + rect.height;
}

void CRectangle::Draw(ICanvas& canvas)
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
    canvas.DrawLine(m_leftTop, { m_leftTop.x, m_rightBottom.y });
    canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_rightBottom);
    canvas.DrawLine(m_rightBottom, { m_rightBottom.x, m_leftTop.y });
    canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_leftTop);

    auto fillColor = GetFillStyle()->GetColor();
    if (fillColor)
    {
        std::vector<Point> points = { 
            m_leftTop, 
            { m_leftTop.x, m_rightBottom.y}, 
            m_rightBottom, 
            { m_rightBottom.x, m_leftTop.y } };
        canvas.FillPoligon(points, *fillColor);
    }
}

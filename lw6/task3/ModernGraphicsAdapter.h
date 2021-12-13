#pragma once
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"

using namespace modern_graphics_lib;

class ModernGraphicsLibAdapter :  public graphics_lib::ICanvas
{
public:
    ModernGraphicsLibAdapter(CModernGraphicsRenderer& renderer)
        : m_renderer(renderer)
    {
        m_renderer.BeginDraw();
    }

    ~ModernGraphicsLibAdapter()
    {
        m_renderer.EndDraw();
    }

    void SetColor(uint32_t rgbColor)
    {
        m_color.r = ((rgbColor >> 16) & 0xFF) / 255.0;
        m_color.g = ((rgbColor >> 8) & 0xFF) / 255.0;
        m_color.b = ((rgbColor) & 0xFF) / 255.0;
    }

    void MoveTo(int x, int y)
    {
        m_currentPoint = { x, y };
    }

    void LineTo(int x, int y)
    {
        CPoint pointTo(x, y);
        m_renderer.DrawLine(m_currentPoint, pointTo, m_color);
        m_currentPoint = pointTo;
    }

private:
    CModernGraphicsRenderer& m_renderer;
    CPoint m_currentPoint = {0, 0};
    CRGBAColor m_color = {0, 0, 0, 1};
};
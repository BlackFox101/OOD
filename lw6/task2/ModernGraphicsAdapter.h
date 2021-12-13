#pragma once
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"

using namespace modern_graphics_lib;

class ModernGraphicsLibAdapter :  
    public graphics_lib::ICanvas, 
    public modern_graphics_lib::CModernGraphicsRenderer
{
public:
    ModernGraphicsLibAdapter(ostream& strm)
        : CModernGraphicsRenderer(strm)
    {
        BeginDraw();
    }

    ~ModernGraphicsLibAdapter()
    {
        EndDraw();
    }

    void MoveTo(int x, int y)
    {
        m_currentPoint = { x, y };
    }

    void LineTo(int x, int y)
    {
        CPoint pointTo(x, y);
        DrawLine(m_currentPoint, pointTo);
        m_currentPoint = pointTo;
    }

private:
    CPoint m_currentPoint = {0, 0};
};
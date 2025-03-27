#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t color)
    : m_startPoint(start), m_endPoint(end)
{
    m_outlineColor = color;
}

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return GetLineLength(m_startPoint, m_endPoint);
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

std::string CLineSegment::ToString() const
{
    return "Figure: Line\nArea: " + std::to_string(CLineSegment::GetArea()) + "\nPerimeter: " + std::to_string(CLineSegment::GetPerimeter()) + "\n";
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas)
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

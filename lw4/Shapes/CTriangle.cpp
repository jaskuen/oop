#include "CTriangle.h"

CTriangle::CTriangle(CPoint point1, CPoint point2, CPoint point3, uint32_t fillColor, uint32_t strokeColor)
	: m_point1(point1), m_point2(point2), m_point3(point3), m_fillColor(fillColor), m_outlineColor(strokeColor)
{
}

double CTriangle::GetArea() const
{
	return std::abs((m_point2.x - m_point1.x) * (m_point3.y - m_point1.y) - (m_point3.x - m_point1.x) * (m_point2.y - m_point1.y)) / 2;
}

double CTriangle::GetPerimeter() const
{
	return GetLineLength(m_point1, m_point2) + GetLineLength(m_point1, m_point3) + GetLineLength(m_point2, m_point3);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CTriangle::ToString() const
{
	return "Figure: Triangle\nArea: " + std::to_string(CTriangle::GetArea()) + "\nPerimeter: " + std::to_string(CTriangle::GetPerimeter()) + "\n";
}

CPoint CTriangle::GetVertex1() const
{
	return m_point1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_point2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_point3;
}

void CTriangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> coorditanes =
	{
		m_point1,
		m_point2,
		m_point3
	};

	canvas.FillPolygon(coorditanes, m_fillColor, m_outlineColor);
}

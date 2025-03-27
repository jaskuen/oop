#include "CRectangle.h"

CRectangle::CRectangle(CPoint point, double width, double height, uint32_t fillColor, uint32_t strokeColor)
	: m_point(point), m_width(width), m_height(height), m_fillColor(fillColor), m_outlineColor(strokeColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::ToString() const
{
	return "Figure: Rectangle\nArea: " + std::to_string(CRectangle::GetArea()) + "\nPerimeter: " + std::to_string(CRectangle::GetPerimeter()) + "\n";
}

CPoint CRectangle::GetLeftTop() const
{
	return m_point;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_point.x + m_width, m_point.y + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> coorditanes =
	{
		m_point,
		CPoint(m_point.x + m_width, m_point.y),
		CPoint(m_point.x + m_width, m_point.y + m_height),
		CPoint(m_point.x, m_point.y + m_height)
	};

	canvas.FillPolygon(coorditanes, m_fillColor, m_outlineColor);
}

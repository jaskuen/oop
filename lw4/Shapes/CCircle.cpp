#include "CCircle.h"

#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(CPoint centerPoint, double radius, uint32_t fillColor, uint32_t strokeColor)
	: m_center(centerPoint), m_radius(radius), m_fillColor(fillColor), m_outlineColor(strokeColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::ToString() const
{
	return "Figure: Circle\nArea: " + std::to_string(CCircle::GetArea()) + "\nPerimeter: " + std::to_string(CCircle::GetPerimeter()) + "\n";
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(m_center, m_radius, m_fillColor, m_outlineColor);
}

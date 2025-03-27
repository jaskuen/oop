#pragma once

#include "ISolidShape.h"

class CTriangle : public virtual ISolidShape
{
public:
	CTriangle(CPoint point1, CPoint point2, CPoint point3, uint32_t fillColor, uint32_t strokeColor);

	double GetArea() const;
	double GetPerimeter() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	std::string ToString() const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) override;

private:
	CPoint m_point1, m_point2, m_point3;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};

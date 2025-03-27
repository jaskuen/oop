#pragma once

#include "ISolidShape.h"

class CCircle : public virtual ISolidShape
{
public:
	CCircle(CPoint centerPoint, double radius, uint32_t fillColor, uint32_t strokeColor);

	double GetArea() const;
	double GetPerimeter() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	std::string ToString() const;

	CPoint GetCenter() const;
	double GetRadius() const;

	void Draw(ICanvas& canvas) override;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};

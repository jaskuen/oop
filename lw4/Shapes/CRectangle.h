#pragma once

#include "ISolidShape.h"

class CRectangle : public virtual ISolidShape
{
public:
	CRectangle(CPoint point, double width, double height, uint32_t fillColor, uint32_t strokeColor);

	double GetArea() const;
	double GetPerimeter() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	std::string ToString() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	void Draw(ICanvas& canvas) override;

private:
	CPoint m_point;
	double m_width, m_height;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};

#pragma once

#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint start, CPoint end, uint32_t color);

	double GetArea() const;
	double GetPerimeter() const;
	uint32_t GetOutlineColor() const;
	std::string ToString() const;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void Draw(ICanvas& canvas) override;
private:
	CPoint m_startPoint, m_endPoint;
};

#pragma once
#include "CPoint.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) const = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t borderColor) const = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t lineColor) const = 0;

	virtual ~ICanvas() = default;
};

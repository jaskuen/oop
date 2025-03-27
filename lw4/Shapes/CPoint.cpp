#include "CPoint.h"

CPoint::CPoint(double x, double y) : x(x), y(y) {}

double GetLineLength(CPoint start, CPoint end)
{
	return std::hypot(end.x - start.x, end.y - start.y);
}

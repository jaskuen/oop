#pragma once
#include <cmath>

class CPoint
{
public:
	double x, y;
	CPoint(double x, double y);
};

double GetLineLength(CPoint start, CPoint end);


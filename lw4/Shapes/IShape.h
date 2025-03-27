#pragma once

#include "ICanvasDrawable.h"
#include <string>

class IShape : public virtual ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

protected:
	uint32_t m_outlineColor;
};

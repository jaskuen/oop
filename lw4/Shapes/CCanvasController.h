#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>

#include "CCanvas.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CLineSegment.h"
#include "IShape.h"

using ActionMap = std::unordered_map<std::string, std::function<void()>>;

class CCanvasController
{
public:
	CCanvasController(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintResult();
	void DrawShapes(sf::RenderWindow& window);

private:
	void PrintShape(const IShape* shape);
	void AddRectangle();
	void AddLine();
	void AddCircle();
	void AddTriangle();
	IShape* GetMaxAreaShape() const;
	IShape* GetMinPerimeterShape() const;
	static uint32_t StringToUint32(const std::string& value);

	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_map;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
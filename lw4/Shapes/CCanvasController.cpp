#include "CCanvasController.h"

CCanvasController::CCanvasController(std::istream& input, std::ostream& output)
	: m_input(input), m_output(output)
{
	m_map.emplace("rectangle", [this]() { CCanvasController::AddRectangle(); });
	m_map.emplace("line", [this]() { CCanvasController::AddLine(); });
	m_map.emplace("circle", [this]() { CCanvasController::AddCircle(); });
	m_map.emplace("triangle", [this]() { CCanvasController::AddTriangle(); });
}

void CCanvasController::HandleCommand()
{
	std::string command;
	m_input >> command;

	auto it = m_map.find(command);
	if (it != m_map.end())
	{
		try
		{
			it->second();
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}
		return;
	}
	else
	{
		m_output << "Unknown command!" << std::endl;
	}
}

void CCanvasController::PrintResult()
{
	if (m_shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return;
	}
	m_output << "Shape with max circleArea:" << std::endl;
	CCanvasController::PrintShape(CCanvasController::GetMaxAreaShape());

	m_output << std::endl
		<< "Shape with min circlePerimeter:" << std::endl;
	CCanvasController::PrintShape(CCanvasController::GetMinPerimeterShape());
}

void CCanvasController::DrawShapes(sf::RenderWindow& window)
{
	CCanvas canvas(window);
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CCanvasController::AddRectangle()
{
	double x, y, width, height;
	std::string fillColorString, outlineColorString;
	if (!(m_input >> x && m_input >> y && m_input >> width && m_input >> height && m_input >> fillColorString && m_input >> outlineColorString))
	{
		throw std::invalid_argument("Invalid count of arguments to create rectangle");
	}
	const auto fillColor = CCanvasController::StringToUint32(fillColorString);
	const auto outlineColor = CCanvasController::StringToUint32(outlineColorString);
	auto rectangle = std::make_unique<CRectangle>(CPoint({ x, y }), width, height, fillColor, outlineColor);

	m_shapes.push_back(std::move(rectangle));
}

void CCanvasController::AddLine()
{
	double startX, startY, endX, endY;
	std::string lineColorString;
	if (!(m_input >> startX && m_input >> startY && m_input >> endX && m_input >> endY && m_input >> lineColorString))
	{
		throw std::invalid_argument("Invalid count of arguments to create line");
	}
	const auto lineColor = CCanvasController::StringToUint32(lineColorString);
	auto line = std::make_unique<CLineSegment>(CPoint{ startX, startY }, CPoint{ endX, endY }, lineColor);

	m_shapes.push_back(std::move(line));
}

void CCanvasController::AddCircle()
{
	double x, y, radius;
	std::string fillColorString, outlineColorString;
	if (!(m_input >> x && m_input >> y && m_input >> radius && m_input >> fillColorString && m_input >> outlineColorString))
	{
		throw std::invalid_argument("Invalid count of arguments to create circle");
	}
	const auto fillColor = CCanvasController::StringToUint32(fillColorString);
	const auto outlineColor = CCanvasController::StringToUint32(outlineColorString);
	auto circle = std::make_unique<CCircle>(CPoint{ x, y }, radius, fillColor, outlineColor);

	m_shapes.push_back(std::move(circle));
}

void CCanvasController::AddTriangle()
{
	double x1, y1, x2, y2, x3, y3;
	std::string fillColorString, outlineColorString;
	if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 && m_input >> y2 && m_input >> x3 && m_input >> y3 && m_input >> fillColorString && m_input >> outlineColorString))
	{
		throw std::invalid_argument("Invalid count of arguments to create triangle");
	}
	const auto fillColor = CCanvasController::StringToUint32(fillColorString);
	const auto outlineColor = CCanvasController::StringToUint32(outlineColorString);
	auto triangle = std::make_unique<CTriangle>(
		CPoint{ x1, y1 },
		CPoint{ x2, y2 },
		CPoint{ x3, y3 },
		fillColor,
		outlineColor);

	m_shapes.push_back(std::move(triangle));
}

void CCanvasController::PrintShape(const IShape* shape)
{
	if (shape)
	{
		m_output << shape->ToString();
	}
}

IShape* CCanvasController::GetMaxAreaShape() const
{
	auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
		return a->GetArea() < b->GetArea();
		});

	if (result != m_shapes.end())
	{
		return result->get();
	}

	return nullptr;
}

IShape* CCanvasController::GetMinPerimeterShape() const
{
	auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
		return a->GetPerimeter() < b->GetPerimeter();
		});

	if (result != m_shapes.end())
	{
		return result->get();
	}

	return nullptr;
}

uint32_t CCanvasController::StringToUint32(const std::string& value)
{
	if (value.length() != 6)
	{
		throw std::invalid_argument("Invalid color format. Expected 6-character HEX string.");
	}

	uint32_t color = std::stoul(value, nullptr, 16);

	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;

	return sf::Color(r, g, b).toInteger();
}

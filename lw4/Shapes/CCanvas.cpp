#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) const
{
	std::array line =
	{
		sf::Vertex(sf::Vector2f(float(from.x), float(from.y)), sf::Color(lineColor)),
		sf::Vertex(sf::Vector2f(float(to.x), float(to.y)), sf::Color(lineColor))
	};


	m_window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t borderColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(float(points[i].x), float(points[i].y)));
	}

	polygon.setFillColor(sf::Color(fillColor));
	polygon.setOutlineColor(sf::Color(borderColor));
	polygon.setOutlineThickness(1.0f);

	m_window.draw(polygon);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t lineColor) const
{
	sf::CircleShape circle(radius);
	circle.setPosition({ float(center.x - radius), float(center.y - radius) });
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setOutlineThickness(1.0f);

	m_window.draw(circle);
}

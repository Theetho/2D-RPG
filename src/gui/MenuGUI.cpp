#include "stdafx.h"
#include "Macros.h"
#include "MenuGUI.h"

// Offset so the shape reaches the top of the window.
#define OFFSET_TOP 1.06f

// Constructor
MenuGUI::MenuGUI(sf::RenderWindow &window) 
	: GUI(window)
	, m_componentShape(0)
{
	InitShape();

	m_shape = &m_componentShape;
}
// Destructor
MenuGUI::~MenuGUI()
{
}

void MenuGUI::Update(const float& dt)
{
	if (m_isVisible)
	{
		if (!sf::Joystick::isConnected(0) && (!GUI::s_token || m_isMoving))
			Move<sf::ConvexShape>();
	}
}

void MenuGUI::Render(sf::RenderTarget& target)
{
	target.draw(m_componentShape);
}

void MenuGUI::UpdatePosition(const sf::Vector2f &mouse_position)
{
	//m_shape->setPosition(mouse_position);
	m_componentShape.setPosition(mouse_position - sf::Vector2f(0, m_window.getSize().y * 0.03 * 1.06));
}

void MenuGUI::InitShape()
{
	sf::CircleShape corner(m_window.getSize().y * 0.03);

	// Construct the two round corners of the shape.
	int index = 0;
	for (unsigned i = 0; i < corner.getPointCount(); ++i)
	{
		sf::Vector2f point = corner.getPoint(i);
		if (point.x >= 0 && point.x <= corner.getRadius() && point.y >= corner.getRadius() && point.y <= 2 * corner.getRadius())
		{
			m_componentShape.setPointCount(m_componentShape.getPointCount() + 1);
			m_componentShape.setPoint(index++, point);
		}
	}
	for (unsigned i = 0; i < corner.getPointCount(); ++i)
	{
		sf::Vector2f point = corner.getPoint(i);
		if (point.x >= corner.getRadius() && point.x <= 2 * corner.getRadius() && point.y >= corner.getRadius() && point.y <= 2 * corner.getRadius())
		{
			point.x += m_window.getSize().x * 0.5;
			m_componentShape.setPointCount(m_componentShape.getPointCount() + 1);
			m_componentShape.setPoint(index++, point);
		}
	}
	m_componentShape.setPosition(sf::Vector2f(m_window.getSize().x * 0.25f, 0) - sf::Vector2f(corner.getRadius(), corner.getRadius() * OFFSET_TOP));
	m_componentShape.setFillColor(m_backgroundColor);
	m_componentShape.setOutlineThickness(1);
	m_componentShape.setOutlineColor(sf::Color::Black);
}

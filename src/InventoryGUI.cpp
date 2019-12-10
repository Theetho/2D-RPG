#include "stdafx.h"
#include "Macros.h"
#include "InventoryGUI.h"

InventoryGUI::InventoryGUI(sf::RenderWindow &window)
	: GUI(window)
{
	m_isVisible = false;

	m_componentShape.setSize(sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.8f));
	m_componentShape.setPosition(sf::Vector2f(window.getPosition()) + ((sf::Vector2f(window.getSize()) - m_componentShape.getSize()) / 2.f));
	m_componentShape.setFillColor(m_backgroundColor);

	m_shape = &m_componentShape;
}

InventoryGUI::~InventoryGUI()
{
}

void InventoryGUI::Update(const float &dt)
{
	if (!sf::Joystick::isConnected(0) && (!GUI::s_token || m_isMoving))
		Move<sf::RectangleShape>();
}

void InventoryGUI::Render(sf::RenderTarget &target)
{
	if (m_isVisible)
	{
		target.draw(m_componentShape);
	}
}

void InventoryGUI::UpdatePosition(const sf::Vector2f &mouse_position)
{
	m_shape->setPosition(mouse_position);
	m_componentShape.setPosition(mouse_position);
}

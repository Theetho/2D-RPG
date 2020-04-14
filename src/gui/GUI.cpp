#include "stdafx.h"
#include "Macros.h"
#include "GUI.h"

// Static variables;
bool GUI::s_token = false;
std::list<GUI*> GUI::s_instances;

// Constructor
GUI::GUI(sf::RenderWindow &window) 
	: m_window(window)
	, m_shape(nullptr)
	, m_isVisible(true)
	, m_isMoving(false)
	, m_offset(0, 0)
	, m_backgroundColor(0, 0, 0, 128)
	, m_fontColor(sf::Color::White)
	, m_font()
{
	if (!m_font.loadFromFile("res/fonts/GOTHICB.TTF"))
		std::cerr << "Error while loading font in " << __FILE__ << ". Line " << __LINE__ << std::endl;

	// Store the new component to check for collision.
	GUI::s_instances.push_back(this);
}

// Destructor
GUI::~GUI()
{
	s_instances.remove(this);
}

// Private Function
const sf::Vector2f GUI::GetNewPosition(const sf::FloatRect &intersect) const
{
	// Calculate the minimum offset of the intersection
	float offset_top = std::abs(m_shape->getPosition().y + m_shape->getGlobalBounds().height - intersect.top);
	float offset_left = std::abs(m_shape->getPosition().x + m_shape->getGlobalBounds().width - intersect.left);
	float offset_bottom = std::abs((m_shape->getPosition().y) - (intersect.top + intersect.height));
	float offset_right = std::abs((m_shape->getPosition().x) - (intersect.left + intersect.width));

	float min = std::min(offset_bottom, std::min(offset_left, std::min(offset_right, offset_top)));

	sf::Vector2f new_position(m_shape->getPosition());

	// And then calculate the new position of the GUI
	if (min == offset_bottom)
	{
		if (intersect.top + intersect.height > m_window.getPosition().y + m_window.getSize().y - m_shape->getGlobalBounds().height)
			new_position.y = intersect.top - m_shape->getGlobalBounds().height;
		else
			new_position.y = intersect.top + intersect.height;
	}
	else if (min == offset_top)
	{
		if (intersect.top - m_shape->getGlobalBounds().height < 0)
			new_position.y = intersect.top + intersect.height;
		else
			new_position.y = intersect.top - m_shape->getGlobalBounds().height;
	}
	else if (min == offset_right)
	{
		if (intersect.left + intersect.width > m_window.getPosition().x + m_window.getSize().x - m_shape->getGlobalBounds().width)
			new_position.x = intersect.left - m_shape->getGlobalBounds().width;
		else
			new_position.x = intersect.left + intersect.width;
	}
	else if (min == offset_left)
	{
		if (intersect.left - m_shape->getGlobalBounds().width < 0)
			new_position.x = intersect.left + intersect.width;
		else
			new_position.x = intersect.left - m_shape->getGlobalBounds().width;
	}

	return new_position;
}

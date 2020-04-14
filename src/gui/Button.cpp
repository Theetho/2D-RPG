#include "stdafx.h"
#include "Macros.h"
#include "Button.h"

using namespace sf;

#define SELECTED_COLOR Color(0, 0, 255, 128)

// Constructor
Button::Button(const float &x, const float &y,
const float &w, const float &h,
const std::string &text, sf::Font &font,
const sf::Color &idle_color, const sf::Color &hover_color,
const int &font_size)
: m_font(font)
, m_idle_color(idle_color)
, m_hover_color(hover_color)
, m_font_size(font_size)
, m_click_up(false)
, m_click_down(false)
, m_activated(false)
, m_hovered(false)
, m_selected(false)
{
	// Initialize the global shape, which is a rectangle
	m_shape.setSize(Vector2f(w, h));
	m_shape.setPosition(Vector2f(x, y));
	m_shape.setFillColor(SELECTED_COLOR);
	m_shape.setOutlineColor(SELECTED_COLOR);
	m_shape.setOutlineThickness(15);
	
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(m_idle_color);
	m_text.setCharacterSize(m_font_size);

	// Centers the text on the button
	m_text.setPosition(Vector2f(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width  / 2.f - m_text.getGlobalBounds().width  / 2.f),
		m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 1.35)));
	
	// Resize the button so it is the same as the text inside. As the buttons are only text,
	// the global shape must be the size of the text
	m_shape.setSize(Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height));
	m_shape.setPosition(Vector2f(m_text.getGlobalBounds().left, m_text.getGlobalBounds().top));
}
// Destructor
Button::~Button()
{}
	
// Functions
void Button::Update(const Vector2f &mouse_position)
{
	// If the mouse is over the button
	if (m_shape.getGlobalBounds().contains(mouse_position) && !Joystick::isConnected(0))
	{
		m_hovered = true;
		// If the user clicks on the button
		if (Mouse::isButtonPressed(Mouse::Left))
			m_click_down = true;
		// When the user releases the click and is still over the button (simulate a mouse's button up event)
		else if (m_click_down)
		{
			m_click_up = true;
			m_click_down = false;
		}
	}
	else if (!m_selected) // Only usefull if a controller is pluged in
	{
		if (m_hovered)
			m_hovered = false;
		// Reset the click (because it means the user didn't want to clicked on this button)
		if (m_click_down)
			m_click_down = false;
	}
}

void Button::Render(RenderTarget& target)
{
	// Change the color depending on the button state
	if (m_activated && (m_selected || m_hovered))
		m_text.setFillColor(m_hover_color);
	else if (m_activated)
		m_text.setFillColor(m_idle_color);
	else if (m_hovered || m_selected)
		m_text.setFillColor(m_hover_color);
	else
		m_text.setFillColor(m_idle_color);
	if (m_activated)
		target.draw(m_shape);
	target.draw(m_text);
}


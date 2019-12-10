#include "stdafx.h"
#include "Macros.h"
#include "TextField.h"
#include "Game.h"

using namespace sf;

// Constructor
TextField::TextField(sf::RenderWindow &window, sf::Font &font,
	const float &x, const float &y,
	const float &w, const float &h,
	const std::string &text,
	const sf::Color &idle_color, const sf::Color &hover_color,
	const int &text_size, const bool &onlyLetter)
: Button(x, y, w, h, text, font, idle_color, hover_color, text_size)
, m_textEntered("")
, m_window(window)
, m_isBlinking(false)
, m_isThreadRunning(false)
, m_onlyLetter(onlyLetter)
, m_maxCharacterCount(12)
, m_backgroundColor(0, 0, 0, 128)
{
	
	m_shape.setSize(Vector2f(w, h));
	m_shape.setPosition(Vector2f(x, y));
	m_shape.setFillColor(m_backgroundColor);
	m_shape.setOutlineThickness(0);

	m_text.setPosition(Vector2f(m_shape.getPosition()) + Vector2f(m_shape.getGlobalBounds().width * 0.02, m_shape.getGlobalBounds().height * 0.1));
	
	m_textRendered.setString(m_textEntered);
	m_textRendered.setFont(m_font);
	m_textRendered.setFillColor(m_idle_color);
	m_textRendered.setCharacterSize(m_font_size);
	m_textRendered.setPosition(m_text.getPosition());
}
// Destructor
TextField::~TextField()
{}

// Functions
void TextField::Update(const Vector2f &mouse_position)
{
	Button::Update(mouse_position);
}

void TextField::Render(RenderTarget &target)
{
	if (m_activated)
	{
		// Reset the blinking state
		m_isBlinking = false;
		// Set the background black
		m_backgroundColor = Color(0, 0, 0, 128);
		m_shape.setFillColor(m_backgroundColor);

		target.draw(m_shape);
		target.draw(m_textRendered);
	}
	// If the user entered a text but is not over the button anymore
	else if (m_textEntered != "")
	{
		if (!m_isBlinking)
		{
			// Set background transparent
			m_backgroundColor = Color::Transparent;
		}
		m_shape.setFillColor(m_backgroundColor);
		target.draw(m_shape);
		target.draw(m_textRendered);
	}
	// If the user did not yet enter a text and is not over the button
	else
	{
		Button::Render(target);
		if (!m_isBlinking)
		{
			// Set background transparent
			m_backgroundColor = Color::Transparent;
		}
		m_shape.setFillColor(m_backgroundColor);
		target.draw(m_shape);
	}
}
void TextField::HandleInput()
{
	if (Game::s_event.type == sf::Event::TextEntered) 
	{
		int input = Game::s_event.text.unicode;
		// Escape char
		if (input == 27)
		{
			this->Deactivate();
		}
		// Backspace char
		else if (input == '\b')
		{
			RemoveChar();
		}
		else if (m_onlyLetter)
		{	
			//	Capital char			   ||	Normal char
			if ((input > 64 && input < 91) || (input > 96 && input < 123))
				AddChar(input);
		}
		else
		{
			AddChar(input);
		}
	}
}

void TextField::Activate()
{
	Button::Activate();
	m_window.setMouseCursorVisible(false);
}

void TextField::Deactivate()
{
	Button::Deactivate();
	m_window.setMouseCursorVisible(true);
}

void TextField::Blink()
{
	// Set the background to RED. This function is used for example
	// when the user try to launch the game without entering a pseudo.
	m_isBlinking = true;
	m_backgroundColor = sf::Color(255, 0, 0, 128);
}

// Setter
void TextField::SetPosition(const float &x, const float &y)
{ 
	m_shape.setPosition(x, y);
	m_text.setPosition(Vector2f(GetPosition()) + Vector2f(m_shape.getGlobalBounds().width * 0.02, m_shape.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 1.35));
	m_textRendered.setPosition(m_text.getPosition());
}

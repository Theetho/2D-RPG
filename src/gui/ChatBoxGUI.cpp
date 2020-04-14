#include "stdafx.h"
#include "Macros.h"
#include "ChatBoxGUI.h"

#define MAX_CHARACTER_COUNT 50
#define MAX_PREVIOUS_MESSAGES_COUNT 6
#define LOSE_FOCUS_TIME 3
#define TEXT_FIELD_COLOR sf::Color(0, 0, 0, 188)

ChatBoxGUI::ChatBoxGUI(sf::RenderWindow &window, Player &player) 
	: GUI(window)
	, m_player(player)
	, m_commandHandler(*this)
	, m_textField(nullptr)
	, m_hovered(false)
	, m_selected(false)
	, m_quit(false)
{
	InitComponentShape();
	InitTextBox();
	InitKeysPressed();

	m_textField = new TextField(m_window, m_font, m_componentShape.getPosition().x + m_componentShape.getSize().x * 0.05f, m_componentShape.getPosition().y + m_componentShape.getSize().y * 0.80f, m_componentShape.getSize().x * 0.90f, m_componentShape.getSize().y * 0.15f, "", m_backgroundColor + sf::Color(0, 0, 0, 60), sf::Color(0, 0, 0, 50), 0.01f * m_window.getSize().x);
	m_textField->SetMaxSize(MAX_CHARACTER_COUNT);

	m_field.setSize(m_textField->GetSize());
	m_field.setPosition(m_textField->GetPosition());
	m_field.setFillColor(m_backgroundColor);

	m_previousMessages.first = 0;

	m_shape = &m_componentShape;
}

ChatBoxGUI::~ChatBoxGUI()
{
	delete m_textField;
}

void ChatBoxGUI::Update(const float & dt)
{
	if (m_isVisible)
	{
		// If the user presses "Escape" and if the text field has the focus.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_textField->GetActivated())
		{
			m_quit = true;
		}
		// When the user releases "Escape" to quit.
		else if (m_quit)
		{
			Deactivate();
			m_quit = false;
		}
		// When the text field id hovered or activated.
		else if (m_textField->GetHovered() || m_textField->GetActivated())
		{
			m_hovered = true;
		}
		// If the user clicks somewhere else or if enough time was spend since the selection. 
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || (m_selected && (m_timer += dt) && m_timer >= LOSE_FOCUS_TIME))
		{
			m_selected = false;
			m_hovered = false;
		}
		else
			m_hovered = false;

		// Get the focus of the text field when user presses "Enter".
		// Display the text entered if their is one.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_textField->GetTextEntered() != "")
		{
			DisplayMessage();
			m_selected = true;
			m_timer = 0;
			m_previousMessages.first = std::max(static_cast<int>(m_previousMessages.second.size() - 1), 0);
			Deactivate();
		}

		// Get the user inputs.
		DisplayPreviousMessage();

		// Update the text field.
		UpdateTextField();

		// Check for Drag&Drop.
		if (!sf::Joystick::isConnected(0) && (!GUI::s_token || m_isMoving))
			Move<sf::RectangleShape>();
	}
}

void ChatBoxGUI::Render(sf::RenderTarget &target)
{
	if (m_isVisible)
	{
		if (m_hovered || m_selected)
		{
			// Draw the text box.
			target.draw(m_componentShape);
			m_textField->SetRenderColor(m_fontColor);
			// Draw the text field lighter.
			m_field.setFillColor(TEXT_FIELD_COLOR);
			for (auto &it : m_text)
			{
				// Admin's Messages (without '->') are in yellow, else the normal font color
				it.setFillColor(it.getString()[0] == '-' && it.getString()[1] == '>' ? m_fontColor : sf::Color::Yellow);
				target.draw(it);
			}
		}
		else
		{
			m_textField->SetRenderColor(m_backgroundColor);
			m_field.setFillColor(m_backgroundColor);
		}

		// Else if the box is neither selected nor hovered, draw the field.
		if (!m_selected && !m_hovered)
			target.draw(m_field);
		m_textField->Render(target);
	}
}

void ChatBoxGUI::UpdatePosition(const sf::Vector2f &mouse_position)
{
	m_shape->setPosition(mouse_position);
	m_componentShape.setPosition(mouse_position);
	m_textField->SetPosition(m_componentShape.getPosition().x + m_componentShape.getSize().x * 0.05f, m_componentShape.getPosition().y + m_componentShape.getSize().y * 0.80f);
	m_field.setPosition(m_textField->GetPosition());
	sf::Vector2f tmp(m_componentShape.getPosition() + sf::Vector2f(m_componentShape.getSize().x * 0.05, m_componentShape.getSize().y * 0.05));
	// Display the different lines in the text box.
	for (auto &it : m_text)
	{
		it.setPosition(tmp);
		tmp.y += m_componentShape.getSize().y * LINE_HEIGHT;
	}
}

void ChatBoxGUI::UpdateTextField()
{
	if (m_textField->GetPressed())
	{
		m_textField->Activate();
		m_textField->SetPressed(false);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_textField->Deactivate();

	m_textField->Update(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
}

void ChatBoxGUI::UpdatePreviousMessages()
{
	// If the number of previous messages stored is max, then 
	if (m_previousMessages.second.size() == MAX_PREVIOUS_MESSAGES_COUNT && m_previousMessages.second.back() != m_textField->GetTextEnteredConst() && m_textField->GetTextEnteredConst() != "")
	{
		// Override each previous message with the latest before it, and push the new one
		// at the end of the vector.
		for (unsigned int i = 0; i < m_previousMessages.second.size() - 1; ++i)
			m_previousMessages.second[i] = m_previousMessages.second[i + static_cast<unsigned int>(1)];
		m_previousMessages.second[m_previousMessages.second.size() - 1] = m_textField->GetTextEnteredConst();
	}
	// Else if the message is not the last one and is not "", push it inside the vector.
	else if (m_previousMessages.second.size() && m_previousMessages.second.back() != m_textField->GetTextEnteredConst() && m_textField->GetTextEnteredConst() != "")
			m_previousMessages.second.push_back(m_textField->GetTextEnteredConst());
	else 
		m_previousMessages.second.push_back(m_textField->GetTextEnteredConst());
}

// Initialize the text box with the "Welcome" message.
void ChatBoxGUI::InitTextBox()
{
	sf::Vector2f textPosition(m_componentShape.getPosition() + sf::Vector2f(m_componentShape.getSize().x * 0.05, m_componentShape.getSize().y * 0.05));
	std::string text;
	std::ifstream config_file("res/config/text/welcome.cfg");
	if (config_file.is_open())
	{
		while (std::getline(config_file, text, '\n'))
		{
			if (text == "_") text = "";
			sf::Text newText(text, m_font, 0.01 * m_window.getSize().x);
			m_text.push_back(newText);
			m_text.back().setPosition(textPosition);
			m_text.back().setFillColor(sf::Color::Yellow);
			textPosition.y += m_componentShape.getSize().y * LINE_HEIGHT;
		}
		config_file.close();
	}
}

void ChatBoxGUI::InitKeysPressed()
{
	m_keysPressed["UP"] = false;
	m_keysPressed["DOWN"] = false;
}

void ChatBoxGUI::InitComponentShape()
{
	m_componentShape.setSize(sf::Vector2f(m_window.getSize().x * 0.25f, m_window.getSize().y * 0.25f));
	m_componentShape.setPosition(0, m_window.getSize().y - m_componentShape.getSize().y);
	m_componentShape.setOutlineThickness(1);
	m_componentShape.setOutlineColor(sf::Color::Black);
	m_componentShape.setFillColor(m_backgroundColor);
}
void ChatBoxGUI::DisplayMessage()
{
	UpdatePreviousMessages();
	
	// Forward the command to the command handler.
	if (m_textField->GetTextEntered()[0] == '/')
		m_commandHandler.HandleCommand();
	else
	{
		// "Push" every message to the one on top of it.
		auto it = m_text.begin();
		auto next = ++m_text.begin();
		while (next != m_text.end())
		{
			(it++)->setString((next++)->getString());
		}
		m_text.back().setString("-> " + m_textField->GetTextEntered());
	}
	// Reset the text entered.
	m_textField->SetTextEntered("");
}

void ChatBoxGUI::DisplayPreviousMessage()
{
	// The booleans simulate a key released event.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		m_keysPressed["UP"] = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		m_keysPressed["DOWN"] = true;
	else if (m_keysPressed["UP"])
	{
		m_keysPressed["UP"] = false;
		if (m_previousMessages.second.size())
		{
			try
			{
				m_textField->SetTextEntered(m_previousMessages.second[m_previousMessages.first]);
			}
			catch (...)
			{
				m_textField->SetTextEntered("");
			}
			if (m_previousMessages.first > 0)
				--m_previousMessages.first;			
		}
	}
	else if (m_keysPressed["DOWN"])
	{
		m_keysPressed["DOWN"] = false;
		if (m_previousMessages.second.size())
		{
			try
			{
				m_textField->SetTextEntered(m_previousMessages.second[m_previousMessages.first]);
			}
			catch (...)
			{
				m_textField->SetTextEntered("");
			}
			if (m_previousMessages.first < m_previousMessages.second.size() - 1)
				++m_previousMessages.first;
		}
	}

}

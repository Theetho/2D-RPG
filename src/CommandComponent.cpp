#include "stdafx.h"
#include "Macros.h"
#include "CommandComponent.h"
#include "ChatBoxGUI.h"

CommandComponent::CommandComponent(ChatBoxGUI& chat_box) : 
m_ChatBox(chat_box)
{
	InitSlashHelp();
}

CommandComponent::~CommandComponent()
{
}

void CommandComponent::HandleCommand()
{
	std::string &text = m_ChatBox.m_textField->GetTextEntered();
	if (text == "/clear")
	{
		for (auto& it : m_ChatBox.m_text)
			it.setString("");
	}
	else if (text == "/help") 
	{
		m_ChatBox.m_text = m_text;
	}
	else if (text == "/stuck")
	{
		m_ChatBox.m_player.GetSprite().setPosition(m_ChatBox.m_window.getSize().x / 2, m_ChatBox.m_window.getSize().y / 2);
	}
	else if (text.find("/xp ") != std::string::npos)
	{
		text.erase(text.begin(), text.begin() + 4);
		int amount = std::atoll(text.data());
		if (amount > 0)
			m_ChatBox.m_player.GetStatistics().AddExp(amount);
		else if (amount < 0)
			m_ChatBox.m_player.GetStatistics().RemoveExp(-amount);
		else
		{
			if (text.find("-level ") != std::string::npos)
			{
				text.erase(text.begin(), text.begin() + 7);
				int level = std::atoi(text.data());
				if (level > 0 && level <= 50)
				{
					m_ChatBox.m_player.GetStatistics().SetLevel(level);
				}
			}
		}
	}
}

void CommandComponent::InitSlashHelp()
{
	sf::Vector2f textPosition(m_ChatBox.m_componentShape.getPosition() + sf::Vector2f(m_ChatBox.m_componentShape.getSize().x * 0.05, m_ChatBox.m_componentShape.getSize().y * 0.05));
	std::string text;
	std::ifstream config_file("res/config/text/help.cfg");
	if (config_file.is_open())
	{
		while (std::getline(config_file, text, '\n'))
		{
			if (text == "_") text = "";
			sf::Text newText(text, m_ChatBox.m_font, 0.01 * m_ChatBox.m_window.getSize().x);
			m_text.push_back(newText);
			m_text.back().setPosition(textPosition);
			m_text.back().setFillColor(sf::Color::Yellow);
			textPosition.y += m_ChatBox.m_componentShape.getSize().y * LINE_HEIGHT;
		}
		config_file.close();
	}
}

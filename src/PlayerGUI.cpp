#include "stdafx.h"
#include "Macros.h"
#include "PlayerGUI.h"

// Constructor
PlayerGUI::PlayerGUI(sf::RenderWindow& window, Player &player, const std::string& player_name)
	: GUI(window)
	, m_player(player)
{
	// Create the circle with the level inside.
	m_playerLevel.first.setRadius(m_window.getSize().x * 0.015);
	m_playerName.setString(player_name);
	m_playerName.setCharacterSize(25 * m_window.getSize().y / 1080);
	m_playerName.setFont(m_font);

	InitComponentShape();

	m_playerName.setPosition(m_componentShape.getPosition().x + m_componentShape.getSize().x * 0.01, m_componentShape.getPosition().y + m_componentShape.getSize().y * 0.1);
	m_playerName.setFillColor(m_fontColor);
	
	InitPlayerLevelShape();
	
	InitHPBar();
	InitEXPBar();
	InitManaBar();

	m_shape = &m_componentShape;
}
// Destructor
PlayerGUI::~PlayerGUI()
{}

// Functions
void PlayerGUI::Update(const float & dt)
{
	if (m_isVisible)
	{
		// Check Drag&Drop
		if (!sf::Joystick::isConnected(0) && (!GUI::s_token || m_isMoving))
			Move<sf::RectangleShape>();

		// Update the size and the filling of the components
		// TODO : check if you can't update only when it changes.
		long long currentXp = m_player.GetStatistics().GetCurrentLevelExp();
		long long nextXp = m_player.GetStatistics().GetExpForLevel(m_player.GetStatistics().GetLevel() + 1);
		float previous_next = m_player.GetStatistics().GetExpForLevel(m_player.GetStatistics().GetLevel());
		if (m_player.GetStatistics().GetLevel() < 50)
			m_EXPBar.first.setSize(sf::Vector2f(m_EXPBar.second.getSize().x * (static_cast<double>(currentXp - previous_next) / static_cast<double>(nextXp - previous_next)), m_EXPBar.second.getSize().y));
		else 
			m_EXPBar.first.setSize(sf::Vector2f(m_EXPBar.second.getSize().x, m_EXPBar.second.getSize().y));
		m_EXPValue.setString(std::to_string(currentXp) + "/" + std::to_string(nextXp));

		long currentHp = m_player.GetStatistics().GetCurrentHP();
		long maxHp = m_player.GetStatistics().GetMaxHP();
		m_HPBar.first.setSize(sf::Vector2f(m_HPBar.second.getSize().x * static_cast<double>(currentHp) / static_cast<double>(maxHp), m_HPBar.second.getSize().y));
		
		m_HPValue.setString(std::to_string(currentHp) + "/" + std::to_string(maxHp));

		long currentMana = m_player.GetStatistics().GetCurrentMana();
		long maxMana = m_player.GetStatistics().GetMaxMana();
		m_ManaBar.first.setSize(sf::Vector2f(m_ManaBar.second.getSize().x * static_cast<double>(currentMana) / static_cast<double>(maxMana), m_ManaBar.second.getSize().y));
		
		m_ManaValue.setString(std::to_string(currentMana) + "/" + std::to_string(maxMana));

		std::string level = std::to_string(m_player.GetStatistics().GetLevel());
		m_playerLevel.second.setString(level);

		// Update texts' positions
		if (level.size() > 1)
			m_playerLevel.second.setPosition(m_playerLevel.first.getPosition() + sf::Vector2f(m_playerLevel.first.getRadius() / 2.f, m_playerLevel.first.getRadius() / 2.f));
		else
			m_playerLevel.second.setPosition(m_playerLevel.first.getPosition() + sf::Vector2f((m_playerLevel.first.getRadius() + m_playerLevel.second.getGlobalBounds().width) / 2.f, m_playerLevel.first.getRadius() / 2.f));
		m_HPValue.setPosition(m_HPBar.second.getPosition() + sf::Vector2f((m_HPBar.second.getSize().x - m_HPValue.getGlobalBounds().width) / 2, 0));
		m_EXPValue.setPosition(m_EXPBar.second.getPosition() + sf::Vector2f((m_EXPBar.second.getSize().x - m_EXPValue.getGlobalBounds().width) / 2, 0));
		m_ManaValue.setPosition(m_ManaBar.second.getPosition() + sf::Vector2f((m_ManaBar.second.getSize().x - m_ManaValue.getGlobalBounds().width) / 2, 0));
	}
}

void PlayerGUI::Render(sf::RenderTarget& target)
{
	if (m_isVisible)
	{
		target.draw(m_componentShape);
		target.draw(m_HPBar.first);
		target.draw(m_EXPBar.first);
		target.draw(m_ManaBar.first);
		target.draw(m_HPBar.second);
		target.draw(m_EXPBar.second);
		target.draw(m_ManaBar.second);
		target.draw(m_playerLevel.first);
		target.draw(m_playerName);
		target.draw(m_playerLevel.second);
		target.draw(m_HPValue);
		target.draw(m_EXPValue);
		target.draw(m_ManaValue);
	}
}

void PlayerGUI::UpdatePosition(const sf::Vector2f & mouse_position)
{
	// Update all the position based on the new position of the component shape (Text are updated in Update())
	m_shape->setPosition(mouse_position);
	m_componentShape.setPosition(m_shape->getPosition());
	m_playerName.setPosition(m_componentShape.getPosition().x + m_componentShape.getSize().x * 0.01, m_componentShape.getPosition().y + m_componentShape.getSize().y * 0.1);
	if (m_playerName.getGlobalBounds().width > m_playerLevel.first.getRadius() * 2)
		m_playerLevel.first.setPosition(m_playerName.getPosition() + sf::Vector2f(m_playerName.getGlobalBounds().width / 2 - m_playerLevel.first.getRadius(), m_playerName.getGlobalBounds().height + m_playerLevel.first.getRadius() / 2));
	else
		m_playerLevel.first.setPosition(m_playerName.getPosition() + sf::Vector2f(0, m_playerName.getGlobalBounds().height + m_playerLevel.first.getRadius() / 2));
	m_HPBar.first.setPosition(m_playerName.getPosition() + sf::Vector2f(std::max(m_playerName.getGlobalBounds().width, m_playerLevel.first.getRadius() * 2) + m_window.getSize().y * 0.01, 0));
	m_EXPBar.first.setPosition(m_HPBar.first.getPosition().x, m_HPBar.first.getPosition().y + m_window.getSize().y * 0.01 + m_EXPBar.first.getSize().y);
	m_ManaBar.first.setPosition(m_EXPBar.first.getPosition().x, m_EXPBar.first.getPosition().y + m_window.getSize().y * 0.01 + m_ManaBar.first.getSize().y);
	m_HPBar.second.setPosition(m_HPBar.first.getPosition());
	m_EXPBar.second.setPosition(m_EXPBar.first.getPosition());
	m_ManaBar.second.setPosition(m_ManaBar.first.getPosition());
}

void PlayerGUI::InitPlayerLevelShape()
{
	m_playerLevel.first.setFillColor(m_backgroundColor);
	m_playerLevel.first.setOutlineColor(m_fontColor);
	m_playerLevel.first.setOutlineThickness(2);

	if (m_playerName.getGlobalBounds().width > m_playerLevel.first.getRadius() * 2)
		m_playerLevel.first.setPosition(m_playerName.getPosition() + sf::Vector2f(m_playerName.getGlobalBounds().width / 2 - m_playerLevel.first.getRadius(), m_playerName.getGlobalBounds().height + m_playerLevel.first.getRadius() / 2));
	else
		m_playerLevel.first.setPosition(m_playerName.getPosition() + sf::Vector2f(0, m_playerName.getGlobalBounds().height + m_playerLevel.first.getRadius() / 2));
	m_playerLevel.second.setString("1");
	m_playerLevel.second.setCharacterSize(25 * m_window.getSize().y / 1080);
	m_playerLevel.second.setFont(m_font);
	m_playerLevel.second.setFillColor(m_fontColor);
	m_playerLevel.second.setPosition(m_playerLevel.first.getPosition() + sf::Vector2f((m_playerLevel.first.getRadius() + m_playerLevel.second.getGlobalBounds().width) / 2.f, m_playerLevel.first.getRadius() / 2.f));

}

void PlayerGUI::InitComponentShape()
{
	m_componentShape.setSize(sf::Vector2f(m_window.getSize().x * 0.11 + std::max(m_playerName.getGlobalBounds().width, m_playerLevel.first.getRadius() * 2), m_window.getSize().y * 0.11));
	m_componentShape.setPosition(0, 0);
	m_componentShape.setOutlineThickness(1);
	m_componentShape.setOutlineColor(sf::Color::Black);
	m_componentShape.setFillColor(m_backgroundColor);
}

void PlayerGUI::InitManaBar()
{
	m_ManaBar.first.setSize(m_EXPBar.first.getSize());
	m_ManaBar.first.setPosition(m_EXPBar.first.getPosition().x, m_EXPBar.first.getPosition().y + m_window.getSize().y * 0.01 + m_ManaBar.first.getSize().y);
	m_ManaBar.first.setFillColor(sf::Color::Blue);
	m_ManaBar.second.setSize(m_ManaBar.first.getSize());
	m_ManaBar.second.setPosition(m_ManaBar.first.getPosition());
	m_ManaBar.second.setOutlineColor(m_fontColor);
	m_ManaBar.second.setOutlineThickness(1);
	m_ManaBar.second.setFillColor(sf::Color::Transparent);
	std::string hp_level = std::to_string(m_player.GetStatistics().GetMaxHP());
	m_ManaValue.setString(hp_level + '/' + hp_level);
	m_ManaValue.setCharacterSize(20 * m_window.getSize().y / 1080);
	m_ManaValue.setFont(m_font);
	m_ManaValue.setFillColor(m_fontColor);
	m_ManaValue.setPosition(m_ManaBar.first.getPosition() + sf::Vector2f((m_ManaBar.first.getSize().x - m_ManaValue.getGlobalBounds().width) / 2, 0));
}

void PlayerGUI::InitHPBar()
{
	m_HPBar.first.setSize(sf::Vector2f(m_window.getSize().x * 0.10, m_window.getSize().y * 0.02));
	m_HPBar.first.setPosition(m_playerName.getPosition() + sf::Vector2f(std::max(m_playerName.getGlobalBounds().width, m_playerLevel.first.getRadius() * 2) + m_window.getSize().y * 0.01, 0));
	m_HPBar.first.setFillColor(sf::Color::Red);
	m_HPBar.second.setSize(m_HPBar.first.getSize());
	m_HPBar.second.setPosition(m_HPBar.first.getPosition());
	m_HPBar.second.setOutlineColor(m_fontColor);
	m_HPBar.second.setOutlineThickness(1);
	m_HPBar.second.setFillColor(sf::Color::Transparent);
	std::string mana_level = std::to_string(m_player.GetStatistics().GetMaxMana());
	m_HPValue.setString(mana_level + '/' + mana_level);
	m_HPValue.setCharacterSize(20 * m_window.getSize().y / 1080);
	m_HPValue.setFont(m_font);
	m_HPValue.setFillColor(m_fontColor);
	m_HPValue.setPosition(m_HPBar.first.getPosition() + sf::Vector2f((m_HPBar.first.getSize().x - m_HPValue.getGlobalBounds().width) / 2, 0));
}

void PlayerGUI::InitEXPBar()
{
	m_EXPBar.first.setSize(m_HPBar.first.getSize());
	m_EXPBar.first.setPosition(m_HPBar.first.getPosition().x, m_HPBar.first.getPosition().y + m_window.getSize().y * 0.01 + m_EXPBar.first.getSize().y);
	m_EXPBar.first.setFillColor(sf::Color(50, 205, 50, 255));
	m_EXPBar.second.setSize(m_EXPBar.first.getSize());
	m_EXPBar.second.setPosition(m_EXPBar.first.getPosition());
	m_EXPBar.second.setOutlineColor(m_fontColor);
	m_EXPBar.second.setOutlineThickness(1);
	m_EXPBar.second.setFillColor(sf::Color::Transparent);
	std::string next_level_exp = std::to_string(m_player.GetStatistics().GetNextLevelExp());
	m_EXPValue.setString("0/"+ next_level_exp);
	m_EXPValue.setCharacterSize(20 * m_window.getSize().y / 1080);
	m_EXPValue.setFont(m_font);
	m_EXPValue.setFillColor(m_fontColor);
	m_EXPValue.setPosition(m_EXPBar.first.getPosition() + sf::Vector2f((m_EXPBar.first.getSize().x - m_EXPValue.getGlobalBounds().width) / 2, 0));
}



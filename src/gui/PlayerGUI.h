#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "GUI.h"
#include "entities/Player.h"

class PlayerGUI : public GUI
{
public:
	// Constructor
	PlayerGUI(sf::RenderWindow& window, Player &player, const std::string &player_name);
	// Destructor
	~PlayerGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget& target);

private:
	// Private function
	void UpdatePosition(const sf::Vector2f& mouse_position);
	void InitPlayerLevelShape();
	void InitComponentShape();
	void InitManaBar();
	void InitHPBar();
	void InitEXPBar();

	Player &m_player;

	sf::RectangleShape m_componentShape;

	// Health bar
	std::pair<sf::RectangleShape, sf::RectangleShape> m_HPBar;
	sf::Text m_HPValue;

	// Exp bar
	std::pair<sf::RectangleShape, sf::RectangleShape> m_EXPBar;
	sf::Text m_EXPValue;

	// Mana bar
	std::pair<sf::RectangleShape, sf::RectangleShape> m_ManaBar;
	sf::Text m_ManaValue;

	// Infos
	sf::Text m_playerName;
	std::pair<sf::CircleShape, sf::Text> m_playerLevel;
};


#endif // !PLAYER_GUI_H


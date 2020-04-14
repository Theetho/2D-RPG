#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "components/StatisticsComponent.h"

class Player : public Entity
{
public:
	// Constructor
	Player(float max_velocity, float x_pos, float y_pos, std::string config_file, std::string name, sf::Font& font, int sprite_scale = 1);
	// Destructor
	virtual ~Player();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget& target);

	// Getter
	sf::Sprite& GetSprite() const { return *m_Sprite; }
	const std::string &GetName() const { return m_Name; }
	StatisticsComponent &GetStatistics() { return m_Statistics; }

private:
	// Pseudo of the player
	std::string m_Name;
	sf::Text m_NameRendered;
	sf::Font& m_font;

	// Attributes of the player
	StatisticsComponent m_Statistics;

	// Private functions
	void InitAnimationComponent(const std::string config_file);
	void InitName();
};

#endif //!_PLAYER_H_
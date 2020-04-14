#ifndef _HITBOX_COMPONENT_H_
#define _HITBOX_COMPONENT_H_

class HitboxComponent
{
public:
	// Constructor
	HitboxComponent(sf::Sprite& sprite, const float width, const float height);
	// Destructor
	virtual ~HitboxComponent();

	// Functions
	void Update();
	void Render(sf::RenderTarget& target) const;

private:
	sf::RectangleShape m_Hitbox;
	sf::Sprite& m_Sprite;
};

#endif // !_HITBOX_COMPONENT_H_


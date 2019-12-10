#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
public:
	// Constructor
	Entity();
	// Destructor
	virtual ~Entity();

	// Virtual functions
	virtual void Update(const float& dt) = 0;
	
	// Functions
	virtual void Move(const float& dt, const float x_motion, const float y_motion);
	virtual void Render(sf::RenderTarget& target);

	// Getters
	MovementComponent& GetMovement() const;
	AnimationComponent& GetAnimation() const;

protected:
	sf::Sprite* m_Sprite;
	std::map<std::string, sf::Texture> m_Textures;
	MovementComponent* m_Movement;
	AnimationComponent* m_Animation;
	HitboxComponent* m_Hitbox;
	
	// Private functions
	virtual void InitSprite();
	virtual void InitMovementComponent(float max_velocity, float acceleration, float deceleration);
	virtual void InitAnimationComponent();
	virtual void InitTextures();
};

#endif //!_ENTITY_H_

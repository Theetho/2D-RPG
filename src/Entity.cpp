#include "stdafx.h"
#include "Macros.h"
#include "Entity.h"

using namespace sf;

// Constructor
Entity::Entity() : 
m_Sprite(nullptr), 
m_Movement(nullptr), 
m_Animation(nullptr), 
m_Hitbox(nullptr)
{}
// Destructor
Entity::~Entity()
{}

// Functions
void Entity::Move(const float& dt, const float x_motion, const float y_motion)
{
	if (m_Sprite && m_Movement)
	{
		m_Movement->Move(dt, x_motion, y_motion);
		m_Sprite->move(m_Movement->GetVelocity());
		// An entity with m_Animation needs to define those four moves
		// Plays the right m_Animation
		if (m_Animation)
		{
			if (m_Movement->GetVelocity().y == 0)
			{
				// Moving left
				if (m_Movement->GetVelocity().x < 0)
				{
					m_Animation->SetSide(AnimationSide::LEFT);
					m_Animation->PlayAnimation(m_Movement->GetVelocity().x, dt, "LEFT");
				}
				// Moving right
				else if (m_Movement->GetVelocity().x > 0)
				{
					m_Animation->SetSide(AnimationSide::RIGHT);
					m_Animation->PlayAnimation(m_Movement->GetVelocity().x, dt, "RIGHT");
				}
			}
			else
			{
				// Moving up
				if (m_Movement->GetVelocity().y < 0)
				{
					m_Animation->SetSide(AnimationSide::UP);
					m_Animation->PlayAnimation(m_Movement->GetVelocity().y, dt, "UP");
				}
				// Moving up
				else if (m_Movement->GetVelocity().y > 0)
				{
					m_Animation->SetSide(AnimationSide::DOWN);
					m_Animation->PlayAnimation(m_Movement->GetVelocity().y, dt, "DOWN");
				}
			}
		}
	}
}

void Entity::Render(RenderTarget& target)
{
	if (m_Sprite)
		target.draw(*m_Sprite);
}

void Entity::InitSprite()
{
	m_Sprite = new Sprite();
	m_Hitbox = new HitboxComponent(*m_Sprite, 64, 64);
}

void Entity::InitAnimationComponent()
{
	m_Animation = new AnimationComponent(*m_Sprite);
}

void Entity::InitTextures()
{}

void Entity::InitMovementComponent(float max_velocity, float acceleration, float deceleration)
{
	m_Movement = new MovementComponent(max_velocity, acceleration, deceleration);
}

// Getters
MovementComponent& Entity::GetMovement() const
{
	if (m_Movement)
		return *m_Movement;
}

AnimationComponent& Entity::GetAnimation() const
{
	if (m_Animation)
		return *m_Animation;
}

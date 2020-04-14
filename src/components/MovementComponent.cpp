#include "stdafx.h"
#include "Macros.h"
#include "MovementComponent.h"

// Constructors
MovementComponent::MovementComponent(float max_velocity, float acceleration, float deceleration) :
m_MaxVelocity(max_velocity), 
m_Velocity({0,0}),
m_Acceleration(acceleration),
m_Deceleration(deceleration)
{}

MovementComponent::MovementComponent(const MovementComponent & other)
{
	m_MaxVelocity = other.m_MaxVelocity;
	m_Acceleration = other.m_Acceleration;
	m_Deceleration = other.m_Deceleration;
	m_Velocity = other.m_Velocity;
}

// Destructor
MovementComponent::~MovementComponent()
{}

// Functions
void MovementComponent::Move(const float & dt, const float dir_x, const float dir_y)
{
	// Update the velocity
	m_Velocity.x += dir_x * m_Acceleration * dt;
	m_Velocity.y += dir_y * m_Acceleration * dt; 
		
	// Checking if the velocity is not over the max velocity
	// Going right
	if (m_Velocity.x > m_MaxVelocity)
	{
		m_Velocity.x = m_MaxVelocity;
	}
	// Going left
	else if (m_Velocity.x < - m_MaxVelocity)
	{
		m_Velocity.x = - m_MaxVelocity;
	}
	// Going down
	if (m_Velocity.y > m_MaxVelocity)
	{
		m_Velocity.y = m_MaxVelocity;
	}
	// Going up
	else if (m_Velocity.y < - m_MaxVelocity)
	{
		m_Velocity.y = - m_MaxVelocity;
	}
}

void MovementComponent::Update(const float & dt, sf::Sprite& sprite)
{
	// Decelerating phase and check that velocity doesn't go below 0
	// Going right
	if (m_Velocity.x > 0)
	{
		m_Velocity.x -= m_Deceleration * dt;
		if (m_Velocity.x < 0)
		{
			m_Velocity.x = 0;
		}
	}
	// Going left
	else if (m_Velocity.x < 0)
	{
		m_Velocity.x += m_Deceleration * dt;
		if (m_Velocity.x > 0)
		{
			m_Velocity.x = 0;
		}
	}
	// Going down
	if (m_Velocity.y > 0)
	{
		m_Velocity.y -= m_Deceleration * dt;
		if (m_Velocity.y < 0)
		{
			m_Velocity.y = 0;
		}
	}
	// Going up
	else if (m_Velocity.y < 0)
	{
		m_Velocity.y += m_Deceleration * dt;
		if (m_Velocity.y > 0)
		{
			m_Velocity.y = 0;
		}
	}
	// Finaly move the sprite with the correct velocity
	sprite.move(m_Velocity);
}

// Operator
MovementComponent MovementComponent::operator=(const MovementComponent & other)
{
	m_MaxVelocity = other.m_MaxVelocity;
	m_Acceleration = other.m_Acceleration;
	m_Deceleration = other.m_Deceleration;
	m_Velocity = other.m_Velocity;

	return *this;
}

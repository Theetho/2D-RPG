#include "stdafx.h"
#include "Macros.h"
#include "HitboxComponent.h"

using namespace sf;

// Constructor
HitboxComponent::HitboxComponent(Sprite& sprite, const float width, const float height) : 
m_Sprite(sprite)
{
	m_Hitbox.setPosition(m_Sprite.getPosition());
	m_Hitbox.setSize(Vector2f(width, height));

	m_Hitbox.setFillColor(Color::Transparent);
	m_Hitbox.setOutlineThickness(1.f);
	m_Hitbox.setOutlineColor(Color::Red);
}
// Destructor
HitboxComponent::~HitboxComponent()
{}

// Functions
void HitboxComponent::Update()
{
	m_Hitbox.setPosition(m_Sprite.getPosition());
}

void HitboxComponent::Render(RenderTarget& target) const
{
	target.draw(m_Hitbox);
}
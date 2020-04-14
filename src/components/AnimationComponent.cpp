#include "stdafx.h"
#include "Macros.h"
#include "AnimationComponent.h"

using namespace sf;

// Constructor
AnimationComponent::AnimationComponent(Sprite& sprite) : 
m_Sprite(sprite), 
m_Side(AnimationSide::DOWN)
{}
// Destructor
AnimationComponent::~AnimationComponent()
{
	for (auto &it : m_Animation)
	{
		delete it.second->m_TextureSheet;
		delete it.second;
	}
}

// Functions
void AnimationComponent::AddAnimation(const std::string key, Texture* texture_sheet, int texture_size, int width, int height, float frame_delay)
{
	// Create and Set a new animation with a "key"
	m_Animation[key] = new Animation(texture_sheet, m_Sprite, texture_size, width, height, frame_delay);
}

void AnimationComponent::PlayAnimation(const float & velocity, const float & dt, const std::string animation)
{
	m_Animation[animation]->Play(velocity, dt);
}

void AnimationComponent::ResetAnimation(const std::string animation)
{
	m_Animation[animation]->Reset();
}

void AnimationComponent::IdleAnimation(const float &dt, const std::string animation)
{
	m_Animation[animation]->Idle(dt);
}
#include "stdafx.h"
#include "Macros.h"
#include "TransitionComponent.h"

using namespace sf;

// Constructor
TransitionComponent::TransitionComponent(unsigned int width, unsigned int height) :
m_Status(TransitionStatus::NONE)
{
	m_Color.r = 0;
	m_Color.g = 0;
	m_Color.b = 0;
	m_Color.a = 0;

	m_TransitionScreen.setSize(Vector2f(width, height));
	m_TransitionScreen.setFillColor(m_Color);
}
TransitionComponent::TransitionComponent(Vector2u size) :
m_Status(TransitionStatus::NONE)
{
	m_Color.r = 0;
	m_Color.g = 0;
	m_Color.b = 0;
	m_Color.a = 0;

	m_TransitionScreen.setSize(Vector2f(size.x, size.y));
	m_TransitionScreen.setFillColor(m_Color);
}
// Destructor
TransitionComponent::~TransitionComponent()
{}

// Functions
void TransitionComponent::Update()
{
	switch (m_Status)
	{
	case TransitionStatus::NONE:
		m_Color.a += 1;
		if (m_Color.a == 255)
			m_Status = TransitionStatus::HALF;
		break;
	case TransitionStatus::HALF:
		m_Status = TransitionStatus::WAIT_COMPLETE;
		break;
	case TransitionStatus::WAIT_COMPLETE:
		m_Color.a -= 1;
		if (m_Color.a == 0)
			m_Status = TransitionStatus::COMPLETE;
		break;
	case TransitionStatus::COMPLETE:
		m_Status = TransitionStatus::NONE;
		break;
	default:
		break;
	}
	m_TransitionScreen.setFillColor(m_Color);
}

void TransitionComponent::Render(RenderTarget& target)
{
	target.draw(m_TransitionScreen);
}
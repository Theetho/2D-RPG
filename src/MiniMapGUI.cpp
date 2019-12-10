#include "stdafx.h"
#include "Macros.h"
#include "MiniMapGUI.h"

using namespace sf;

float MiniMapGUI::s_MiniMapScale = 0.3;

MiniMapGUI::MiniMapGUI(RenderWindow& window, Player &player, Texture& map_texture) 
	: GUI(window/*, player*/)
	, m_player(player)
	, m_MapTexture(map_texture)
{
	MiniMapGUI::s_MiniMapScale = 0.3 * m_window.getSize().y / 1080;
	
	m_PlayerPosition.setRadius(2);
	m_PlayerPosition.setFillColor(Color::Red);

	m_MapShape.setSize(Vector2f(m_MapTexture.getSize()));
	m_MapShape.setTexture(&m_MapTexture);
	m_MapShape.setScale(MiniMapGUI::s_MiniMapScale, MiniMapGUI::s_MiniMapScale);

	m_componentShape.setSize(Vector2f(m_MapShape.getSize().x * MiniMapGUI::s_MiniMapScale, m_MapShape.getSize().y * MiniMapGUI::s_MiniMapScale) 
						+ Vector2f(m_window.getSize().x * 0.01, m_window.getSize().x * 0.01));

	m_componentShape.setPosition(Vector2f(m_window.getSize().x - m_componentShape.getSize().x, 0));
	m_componentShape.setOutlineThickness(1);
	m_componentShape.setOutlineColor(Color::Black);
	m_componentShape.setFillColor(m_backgroundColor);

	m_MapShape.setPosition(m_componentShape.getPosition() + Vector2f(m_componentShape.getSize().x / 2 - m_MapShape.getSize().x * MiniMapGUI::s_MiniMapScale / 2,
		m_componentShape.getSize().y / 2 - m_MapShape.getSize().y * MiniMapGUI::s_MiniMapScale / 2));
	m_MapShape.setTextureRect(IntRect(0, 0, m_MapShape.getSize().x, m_MapShape.getSize().y));
	
	m_shape = &m_componentShape;
}

MiniMapGUI::~MiniMapGUI()
{
}

void MiniMapGUI::Update(const float & dt)
{
	if (m_isVisible)
	{
		if (!Joystick::isConnected(0) && (!GUI::s_token || m_isMoving))
			Move<RectangleShape>();

		if (m_MapTexture.getSize().x > m_MapShape.getSize().x || m_MapTexture.getSize().y > m_MapShape.getSize().y)
			SetTexture(m_MapTexture);

		UpdatePlayerPosition();
	}
}

void MiniMapGUI::Render(RenderTarget& target)
{
	if (m_isVisible)
	{
		target.draw(m_componentShape);
		target.draw(m_MapShape);
		target.draw(m_PlayerPosition);
	}
}

void MiniMapGUI::SetTexture(Texture& texture)
{
	if (&m_MapTexture != &texture)
	{
		m_MapTexture = texture; 
		m_MapShape.setTexture(&m_MapTexture);
	}
	
	m_MapShape.setTextureRect(IntRect((m_player.GetSprite().getPosition().x / m_player.GetSprite().getScale().x - m_MapShape.getSize().x / 2),
									  (m_player.GetSprite().getPosition().y / m_player.GetSprite().getScale().y - m_MapShape.getSize().y / 2),
									   m_MapShape.getTextureRect().width,
									   m_MapShape.getTextureRect().height));

}

void MiniMapGUI::UpdatePosition(const Vector2f & mouse_position)
{
	m_shape->setPosition(mouse_position);
	m_componentShape.setPosition(m_shape->getPosition());
	m_MapShape.setPosition(m_componentShape.getPosition() + Vector2f(m_componentShape.getSize().x / 2 - m_MapShape.getSize().x * MiniMapGUI::s_MiniMapScale / 2,
						   m_componentShape.getSize().y / 2 - m_MapShape.getSize().y * MiniMapGUI::s_MiniMapScale / 2));
}

void MiniMapGUI::UpdatePlayerPosition()
{
	// If the texture is bigger than the shape, the player is always on center of the minimap, and it is the minimap that moves
	if (m_MapTexture.getSize().x > m_MapShape.getSize().x || m_MapTexture.getSize().y > m_MapShape.getSize().y)
		m_PlayerPosition.setPosition(m_componentShape.getPosition() + Vector2f(m_componentShape.getSize().x / 2, m_componentShape.getSize().y / 2));
	// Else, the minimap is fixed and the player moves on it
	else
		m_PlayerPosition.setPosition(m_MapShape.getPosition() + 
						   Vector2f((m_player.GetSprite().getPosition().x / m_player.GetSprite().getScale().x) * MiniMapGUI::s_MiniMapScale,
									(m_player.GetSprite().getPosition().y / m_player.GetSprite().getScale().y) * MiniMapGUI::s_MiniMapScale));
}

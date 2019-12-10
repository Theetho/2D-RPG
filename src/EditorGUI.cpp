#include "stdafx.h"
#include "Macros.h"
#include "EditorGUI.h"

EditorGUI::EditorGUI(sf::RenderWindow &window) 
	: GUI(window)
	, m_selectedTab(0)
{
	m_componentShape.setSize(sf::Vector2f(m_window.getSize().x * 0.015f, m_window.getSize().y));
	m_componentShape.setPosition(0, 0);
	m_componentShape.setFillColor(m_backgroundColor);

	m_shape = &m_componentShape;
}

EditorGUI::~EditorGUI()
{
}

void EditorGUI::Update(const float & dt)
{
	// Change the color of the tabs on the left of the screen if it is hovered.
	for (int i = 0; i < m_tabs.size(); ++i)
	{
		if (m_tabs[i].first.getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				m_selectedTab = i;
			m_tabs[i].first.setFillColor(m_fontColor);
			m_tabs[i].second.setFillColor(m_backgroundColor);
		}
		else
		{
			m_tabs[i].first.setFillColor(m_backgroundColor);
			m_tabs[i].second.setFillColor(m_fontColor);
		}
	}
	// Change the color of the selected tab on the left of the screen.
	if (m_selectedTab >= 0 && m_selectedTab < m_tabs.size())
	{
		m_tabs[m_selectedTab].first.setFillColor(m_fontColor);
		m_tabs[m_selectedTab].second.setFillColor(m_backgroundColor);
	}
}

// Render all the editor tabs.
void EditorGUI::Render(sf::RenderTarget & target)
{
	target.draw(m_componentShape);
	for (auto &it : m_tabs)
	{
		target.draw(it.first);
		target.draw(it.second);
	}
}

// Create the different tabs depending on the number of texture sheet used.
void EditorGUI::Divide(float number_of_textures)
{
	for (unsigned i = 0; i < number_of_textures; ++i)
	{
		sf::RectangleShape tmp_shape(sf::Vector2f(m_componentShape.getSize().x, m_componentShape.getSize().y / number_of_textures));
		tmp_shape.setPosition(0, i * m_componentShape.getSize().y / number_of_textures);
		tmp_shape.setFillColor(m_backgroundColor);
		tmp_shape.setOutlineColor(sf::Color::White);
		tmp_shape.setOutlineThickness(1);
		sf::ConvexShape tmp_conv(3);
		tmp_conv.setPoint(0, sf::Vector2f(tmp_shape.getSize().x / 4, 5 * tmp_shape.getSize().y / 11));
		tmp_conv.setPoint(1, sf::Vector2f( 3 * tmp_shape.getSize().x / 4, 6 * tmp_shape.getSize().y / 11));
		tmp_conv.setPoint(2, sf::Vector2f(tmp_shape.getSize().x / 4, 7 * tmp_shape.getSize().y / 11));
		tmp_conv.setFillColor(m_fontColor);
		tmp_conv.setPosition(tmp_shape.getPosition());
		m_tabs.push_back(std::make_pair(tmp_shape, tmp_conv));
	}
}

// The tabs are not movable.
void EditorGUI::UpdatePosition(const sf::Vector2f & mouse_position)
{
}

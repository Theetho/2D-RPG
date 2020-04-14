#ifndef EDITOR_GUI_H
#define EDITOR_GUI_H

#include "GUI.h"

class EditorGUI : public GUI
{
public:
	// Constructor
	EditorGUI(sf::RenderWindow &window);
	// Destructor
	~EditorGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);
	void Divide(float number_of_textures);
	inline const int &GetSelectedTileset() const { return m_selectedTab; }
	inline const void SetSelectedShape(int value) { m_selectedTab = value; }
	inline const sf::Vector2f &GetSize() const { return m_componentShape.getSize(); }

private:
	sf::RectangleShape m_componentShape;
	// The different tabs of the editor. Each tab has specific tiles.
	std::vector < std::pair<sf::RectangleShape, sf::ConvexShape>> m_tabs;
	// Index of the active tab.
	int m_selectedTab;

	// Private function
	void UpdatePosition(const sf::Vector2f &mouse_position);
};

#endif // !EDITOR_GUI_H


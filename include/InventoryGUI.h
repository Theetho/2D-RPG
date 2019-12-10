#ifndef _INVENTORY_GUI_H_
#define _INVENTORY_GUI_H_

#include "GUI.h"

class InventoryGUI : public GUI
{
public:
	InventoryGUI(sf::RenderWindow &window);
	~InventoryGUI();

	void Update(const float &dt);
	void Render(sf::RenderTarget &target);

private:
	void UpdatePosition(const sf::Vector2f &mouse_position);
	sf::RectangleShape m_componentShape;
};

#endif

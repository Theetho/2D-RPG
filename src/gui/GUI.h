#ifndef _GUI_H_
#define _GUI_H_

//#include "Player.h"

class GUI
{
public:
	GUI(sf::RenderWindow &window);
	virtual ~GUI();

	// Abstract functions
	virtual void Update(const float &dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

	inline void Toggle() { (m_isVisible ? m_isVisible = false : m_isVisible = true); }

	// Token to control the number of moving component (Drag&Drop) : only one at a time.
	// When the token is set to "true", it means that their is already a component which
	// is moving.
	static bool s_token;
private:
	// List of all the instances. It is needed to check the collisions between component.
	static std::list<GUI*> s_instances;
protected:
	bool m_isVisible;
	bool m_isMoving;
	sf::Vector2f m_offset;

	sf::RenderWindow &m_window;
	sf::Font m_font;

	//Player *m_player;

	// Pointer to the abstract class "sf::Shape", to access it no matter the shape
	// of the component (circle, rectangle, ...).
	sf::Shape *m_shape;
	sf::Color m_backgroundColor;
	sf::Color m_fontColor;

	// Private functions
	// Implement how the component must update when it is moved.
	virtual void UpdatePosition(const sf::Vector2f &mouse_position) = 0;

	// Get the new position of the component if it collides with an other.
	virtual const sf::Vector2f GetNewPosition(const sf::FloatRect & intersect) const;

	// Call the UpdatePosition method to move the component. It is a template because
	// the shape can be a circle, a rectangle, ...
	template <typename TypeOfShape = sf::RectangleShape>
	void Move()
	{
		sf::Vector2f mouse_position(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
		// If the component is clicked on and has the token.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isMoving)
		{
			// Shift the mouse position to the center of the component.
			mouse_position -= m_offset;
			sf::Vector2f window_size(m_window.getSize());

			// Handle the cases where the mouse is outside the window.
			if (mouse_position.x < 0)
				mouse_position.x = 0;
			else if (mouse_position.x > window_size.x - m_shape->getGlobalBounds().width)
				mouse_position.x = window_size.x - m_shape->getGlobalBounds().width;
			if (mouse_position.y < 0)
				mouse_position.y = 0;
			else if (mouse_position.y > window_size.y - m_shape->getGlobalBounds().height)
				mouse_position.y = window_size.y - m_shape->getGlobalBounds().height;

			// Call the virtual function to update the position.
			UpdatePosition(mouse_position);
		}
		// If the component is clicked on but doesn't have the token yet.
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_shape->getGlobalBounds().contains(mouse_position))
		{
			// Hide the cursor.
			m_window.setMouseCursorVisible(false);
			// Calculate the offset to the center of the component.
			m_offset = sf::Vector2f(mouse_position - m_shape->getPosition());
			GUI::s_token = true;
			m_isMoving = true;
		}
		// When the user release the click.
		else
		{
			// Check if the component collides with an other instance.
			if (m_isMoving)
			{
				for (auto &it : GUI::s_instances)
				{
					if (it->m_isVisible && it != this)
					{
						if (it->m_shape->getGlobalBounds().intersects(m_shape->getGlobalBounds()))
						{
							m_shape = dynamic_cast<TypeOfShape*>(m_shape);
							UpdatePosition(GetNewPosition(it->m_shape->getGlobalBounds()));
						}
					}
				}
			}
			m_isMoving = false;
			m_window.setMouseCursorVisible(true);
			GUI::s_token = false;
		}
	}
};

#endif // !_GUI_H_


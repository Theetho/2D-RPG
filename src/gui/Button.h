#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{
protected:
	// Main surface of the button
	sf::RectangleShape m_shape;

	// Text on the button
	sf::Font& m_font;
	sf::Text m_text;
	int m_font_size;

	// Colors of the button
	sf::Color m_idle_color;
	sf::Color m_hover_color;

	// States of the button
	bool m_click_down;
	bool m_click_up;
	bool m_activated;
	bool m_hovered;
	bool m_selected; // -> Only usefull when a controller is pluged in : it is the equivalent of hovered
public:
	// Construtor
	Button(const float &x, const float &y, 
		   const float &w, const float &h, 
		   const std::string &text, sf::Font &font, 
		   const sf::Color &idle_color, const sf::Color &hover_color,
		   const int &font_size);
	// Destructor
	virtual ~Button();

	// Functions
	virtual void Update(const sf::Vector2f &mouse_position);
	virtual void Render(sf::RenderTarget &target);
	inline virtual void Activate() { if (!m_activated) m_activated = true; }
	inline virtual void Deactivate() { if (m_activated) m_activated = false;}

	// Getters
	inline sf::Vector2f GetPosition() const { return m_shape.getPosition(); }
	inline sf::Vector2f GetSize() const { return m_shape.getSize(); }
	inline bool GetPressed() const { return m_click_up; }
	inline bool GetActivated() const { return m_activated; }
	inline bool GetHovered() const { return m_hovered; }
	inline bool GetSelected() const { return m_selected; }

	// Setters
	inline void SetPressed(const bool pressed) { m_click_up = pressed; }
	inline void SetHovered(const bool hovered) { m_hovered = hovered; }
	inline void SetSelected(const bool selected) { m_selected = selected; }
};

#endif // !_BUTTON_H_

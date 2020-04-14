#ifndef BUTTON_TEXT_H
#define BUTTON_TEXT_H

#include "Button.h"

class TextField : public Button
{
public:
	// Constructor
	TextField(sf::RenderWindow &window, sf::Font &font, 
		      const float &x = 0, const float &y = 0,
			  const float &w = 0, const float &h = 0, 
			  const std::string &text = "",
			  const sf::Color &idle_color = sf::Color::White, 
		      const sf::Color &hover_color = sf::Color::White,
			  const int &text_size = 0, const bool &onlyLetter = false);
	// Destructor
	virtual ~TextField();

	// Functions
	void Update(const sf::Vector2f &mouse_position);
	void Render(sf::RenderTarget &target);
	void Blink();
	void HandleInput();
	void Activate();
	void Deactivate();

	// Getter
	inline std::string &GetTextEntered() { return m_textEntered; }
	inline std::string GetTextEnteredConst() const { return m_textEntered; }

	// Setter
	inline void SetMaxSize(const int &value) { m_maxCharacterCount = value; }
	inline void SetRenderColor(const sf::Color &color) { m_textRendered.setFillColor(color); }
	inline void SetTextEntered(const std::string &text) { m_textEntered = text; m_textRendered.setString(text); }
	void SetPosition(const float &x, const float &y);

private:
	sf::RenderWindow& m_window;

	// Text entered
	std::string m_textEntered;
	sf::Text m_textRendered;
	// Maximum size of the text entered.
	int m_maxCharacterCount;
	// Background when the text is entered.
	sf::Color m_backgroundColor;
	
	// States of the button
	bool m_isThreadRunning;
	bool m_isBlinking;
	bool m_onlyLetter;
	
	// Private functions
	inline void AddChar(const char &character)
	{
		// Add the character to the text string.
		if (m_textEntered.size() < m_maxCharacterCount)
		{
			m_textEntered += character;
			m_textRendered.setString(m_textEntered);
		}
	}
	inline void RemoveChar()
	{
		// If there is at least one character in the text string.
		if (m_textEntered.size())
		{
			// Remove the character at the end of the string.
			m_textEntered.pop_back();
			m_textRendered.setString(m_textEntered);
		}
	}
};

#endif // !BUTTON_TEXT_H

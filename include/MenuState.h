#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "EditorState.h"
#include "TextField.h"
#include "AnimationComponent.h"

class MenuState : public State
{
public:
	// Constructor
	MenuState(sf::RenderWindow& window, std::stack<State*>& states_stack, const WhichState state, bool &running, const std::string path, const Menu menu_type);
	// Destructor
	virtual ~MenuState();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget& target);
	void HandleInput(const int &input, const float &dt);

	// Getter
	const Menu & GetMenuType() const;

private:
	Menu m_Type;

	sf::RectangleShape m_Background;

	std::map<std::string, sf::Font> m_font;
	
	sf::Text m_Title;
	
	std::map<std::string, Button*> m_Buttons;
	std::pair<Button*, std::string> m_ActivatedButtons;				// The two buttons that are activated in the character menu
	std::pair<int, int> m_SelectedButtons;							// Button that has the "focus"
	std::vector<std::vector<std::string>> m_ButtonsNaviguator;		// Naviguate through the list of buttons when user uses arrow keys or joystick
	bool m_MovedX;													// Booleen to manage the naviguation through the list of buttons
	bool m_MovedY;
	int m_NumberButtons;

	std::map<std::string, sf::Sprite*> m_Sprites;					// The sprites displayed in the character menu
	std::map<std::string, AnimationComponent*> m_SpritesAnimations;	// The sprite's animation that has to be displayed in the character menu
	sf::RectangleShape m_SpritesBackground;							// Background behind the sprites
	int m_SpritesScale;												// Scale of the sprite in the character menu
	
	sf::Cursor m_Cursor;
	
	
	// Private functions
	void UpdateButtons();
	void UpdateCursor();
	void RenderButtons(sf::RenderTarget& target);
	void RenderSprites(sf::RenderTarget& target);
	void InitFonts();
	void InitButtons(const std::string path);
	void InitTitle(const std::string path);
	void InitSprites();
	void InitAnimations();
};

#endif // !_MENU_STATE_H_


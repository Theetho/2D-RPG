#ifndef _CHAT_BOX_GUI_H_
#define _CHAT_BOX_GUI_H_

#include "GUI.h"
#include "TextField.h"
#include "Player.h"
#include "CommandComponent.h"

#define LINE_HEIGHT 0.10f

class ChatBoxGUI : public GUI
{
public:
	ChatBoxGUI(sf::RenderWindow& window, Player &player);
	~ChatBoxGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);

	inline void Activate() { m_textField->Activate(); }
	inline void Deactivate() { m_textField->Deactivate(); }
	inline const bool IsActive() const { return m_textField->GetActivated(); }
	inline void HandleInput() { m_textField->HandleInput(); }

	friend CommandComponent;
private:
	Player &m_player;

	sf::RectangleShape m_componentShape;

	// Private functions
	// Implement how the component must update when it is moved.
	void UpdatePosition(const sf::Vector2f &mouse_position);
	void UpdateTextField();
	void UpdatePreviousMessages();

	void InitTextBox();
	void InitKeysPressed();
	void InitComponentShape();
	
	void DisplayMessage();
	void DisplayPreviousMessage();

	// Timer to hide the box after some time (3secs).
	float m_timer;
	
	// Booleen to display the box when it is hovered.
	bool m_hovered;													
	bool m_selected;	
	// Booleen to wait until the user realeases "Escape" (to close the box).
	bool m_quit;													

	// Field displayed when the box is active.
	TextField *m_textField;		
	// Field displayed when the box is not active.
	sf::RectangleShape m_field;	
	// Text displayed in the chat box.
	std::list<sf::Text> m_text;								
	// The previous messages from the user.
	std::pair<int, std::vector<std::string>> m_previousMessages;
	std::map <std::string, bool> m_keysPressed;

	// Component that executes the commands of the user.
	CommandComponent m_commandHandler;									
};

#endif // !_CHAT_BOX_GUI_H_

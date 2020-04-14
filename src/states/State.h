#ifndef _STATE_H_
#define _STATE_H_

class State
{
public:
	// Constructor
	State(sf::RenderWindow& window, std::stack<State*>& states_stack, const WhichState &state, bool &running);
	// Destructor
	virtual ~State();

	// Virtual functions
	virtual void HandleInput(const int &input, const float &dt) = 0;
	virtual void Update(const float &dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void InitControllerKeys();
	virtual void InitControllerActions();
	virtual void InitKeyboardKeys();
	virtual void InitKeyboardActions();

	// Getters
	virtual const bool& GetQuit() const;
	virtual const WhichState& GetState() const;

protected:
	sf::RenderWindow& m_window;
	std::map < std::string, int> m_Keys;	// Supported keys
	std::map < std::string, int> m_Actions; // Actions associated to those keys
	
	WhichState m_State;						// Actual state
	bool m_quit;							// If the state wants to m_quit
	bool& m_Running;						// End the game if player presses "QUIT"

	sf::Vector2f m_MousePosition;

	std::stack<State*>& m_StatesStack;		// Reference to the stack of States
};

#endif // !_STATE_H_


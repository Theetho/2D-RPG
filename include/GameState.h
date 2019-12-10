#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "TransitionComponent.h"
#include "PlayerGUI.h"
#include "MiniMapGUI.h"
#include "ChatBoxGUI.h"
#include "MenuGUI.h"

class GameState : public State
{
public:
	// Construtor
	GameState(sf::RenderWindow &window, std::stack<State*> &states_stack, const WhichState &state, bool &running, const std::string &path, const int &sprite_scale, const std::string &player_name, sf::Font &player_name_font);
	// Destructor
	virtual ~GameState();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);
	void HandleInput(const int &input, const float &dt);

private:
	// GUI
	std::map<std::string, GUI*> m_GUI;

	// Player
	Player m_player;	
	bool m_CantMove;
	
	// Map managers
	std::map<std::string, Map*> m_Maps;
	std::map<std::string, Map*> m_CollisionsMaps;
	std::string m_CurrentMap;

	TransitionComponent m_Transition;
	sf::Color m_TransitionColor;

	// Camera managers
	sf::View m_PlayerView;
	std::map<std::string, int> m_LockView;
	sf::RectangleShape m_ViewArea;
	
	// Private functions
	void InitMaps(int scale);
	void InitView();
	void InitGUI(const std::string &player_name);
	void ResetView(bool new_map = false);
	void ChangeMap(const sf::Color& color);
	bool CheckSpriteCollision(const float & dt, const std::string movement);
	void MovePlayer(const float &dt);
};

#endif // !_GAME_STATE_H_

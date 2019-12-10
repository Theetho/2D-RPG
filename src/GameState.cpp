#include "stdafx.h"
#include "Macros.h"
#include "GameState.h"
#include "MenuState.h"
#include "InventoryGUI.h"

using namespace sf;

// Function to tranform std::string in AnimationSide::side \see CheckSpriteCollision()
inline AnimationSide StringToSide(const std::string &side)
{
	if (side == "LEFT")
	{
		return AnimationSide::LEFT;
	}
	else if (side == "RIGHT")
	{
		return AnimationSide::RIGHT;
	}
	else if (side == "DOWN")
	{
		return AnimationSide::DOWN;
	}
	else if (side == "UP")
	{
		return AnimationSide::UP;
	}
}

// Construtor
GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states_stack, const WhichState& state, bool& running, const std::string& path, const int& sprite_scale, const std::string& player_name, sf::Font& player_name_font) :
State(window, states_stack, state, running),
m_player(1.f, 0.0, 0.0, path, player_name, player_name_font, sprite_scale),
m_CantMove(false),
m_Transition(m_window.getSize())
{
	InitMaps(sprite_scale);
	InitGUI(player_name);

	m_PlayerView.setSize(m_window.getSize().x, m_window.getSize().y);
	m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetSize().x * sprite_scale / 2, m_Maps[m_CurrentMap]->GetSize().y * sprite_scale / 2);

	InitView();

	// Display the area where the camera can move (Render it to see)
	m_ViewArea.setFillColor(Color::Transparent);
	m_ViewArea.setOutlineColor(Color::Red);
	m_ViewArea.setOutlineThickness(1);
	m_ViewArea.setPosition(m_LockView["LEFT"], m_LockView["UP"]);
	m_ViewArea.setSize(Vector2f(m_LockView["RIGHT"] - (m_window.getSize().y / 2), m_LockView["DOWN"] - (m_window.getSize().y / 2)));
}
// Destructor
GameState::~GameState()
{
	for (auto &it : m_Maps)
		delete it.second;
	for (auto &it : m_CollisionsMaps)
		delete it.second;
	for (auto &it : m_GUI)
		delete it.second;
}

// Functions
void GameState::HandleInput(const int &input, const float & dt)
{
	auto chat_box = static_cast<ChatBoxGUI*>(m_GUI["CHAT_BOX"]);
	if (chat_box->IsActive())
		chat_box->HandleInput();
	else if (input == m_Actions["PAUSE"])				// Open pause menu when "Options" or "Escape" is pressed
		m_StatesStack.push(new MenuState(m_window, m_StatesStack, WhichState::MENU_STATE, m_Running, "res/config/buttons/pause_menu.cfg", Menu::PAUSE_MENU));
	else if (input == m_Actions["ENTER_CHAT"])
		chat_box->Activate();
	else if (Joystick::isConnected(0))					// Only-Joystick inputs
	{
		if (input == m_Actions["TOGGLE_GUI"])
		{
			for (auto &it : m_GUI)
				it.second->Toggle();
		}
	}
	else												// Only-Keyboard inputs
	{
		if (input == m_Actions["TOGGLE_PLAYER_GUI"])
			m_GUI["PLAYER"]->Toggle();
		else if (input == m_Actions["TOGGLE_MINIMAP_GUI"])
			m_GUI["MINI_MAP"]->Toggle();
		else if (input == m_Actions["TOGGLE_INVENTORY_GUI"])
			m_GUI["INVENTORY"]->Toggle();
	}
}

void GameState::ChangeMap(const Color& color)
{
	if (m_CurrentMap == "Courtyard")
	{
		if (color == Color::Blue)
		{
			m_CurrentMap = "Hogwarts_Hallways";
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Green)
		{
			m_CurrentMap = "Library";
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Yellow)
		{
			m_CurrentMap = "Potions_Room";
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Magenta)
		{
			m_CurrentMap = "The_Great_Hall";
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (m_CurrentMap == "Hogwarts_Hallways")
	{
		if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{
		}
	}
	else if (m_CurrentMap == "Library")
	{
		if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
	}
	else if (m_CurrentMap == "Potions_Room")
	{
		if (color == Color::Blue)
		{
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == Color::Magenta)
		{
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == Color::Green)
		{
			m_CurrentMap = "Library";
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (m_CurrentMap == "The_Great_Hall")
	{
		if (color == Color::Magenta)
		{
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == Color::Blue)
		{
			m_player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == Color::Red)
		{

		}
	}
}

void GameState::Update(const float& dt)
{
	m_MousePosition = m_window.mapPixelToCoords(Mouse::getPosition(m_window));

	m_player.Update(dt);

	if (!static_cast<ChatBoxGUI*>(m_GUI["CHAT_BOX"])->IsActive())
		MovePlayer(dt);

	ResetView();

	for (auto &it : m_GUI)
		it.second->Update(dt);

	if (m_CantMove)
	{
		m_Transition.Update();
		if (m_Transition.GetStatus() == TransitionStatus::HALF)
		{
			ChangeMap(m_TransitionColor);
			MiniMapGUI *tmp = static_cast<MiniMapGUI*>(m_GUI["MINI_MAP"]);
			tmp->SetTexture(*m_Maps[m_CurrentMap]->GetTexture());
		}
		else if (m_Transition.GetStatus() == TransitionStatus::COMPLETE)
		{
			m_CantMove = false;
		}
	}
}

void GameState::Render(RenderTarget& target)
{
	// Change the view
	target.setView(m_PlayerView);
	m_Maps[m_CurrentMap]->Render(target);
	m_player.Render(target);
	//target.draw(m_ViewArea); // Render the camera area

	// Reset the view
	target.setView(m_window.getDefaultView());
	
	for (auto &it : m_GUI)
		it.second->Render(target);
	
	if (m_CantMove)
	{
		m_Transition.Render(target);
	}

}

/////////////////////////////////////////////////////////////////////
/// Initializes the map of Maps with the parameters in the files "Maps/Maps.cfg"
/// Format : 
/// Map_name >> map_path >> collision_map_path
/////////////////////////////////////////////////////////////////////
void GameState::InitMaps(int scale)
{
	std::ifstream config_file("res/config/maps/maps.cfg");
	if (config_file.is_open())
	{
		std::string map_name = "", map_path = "", collision_map_path = "", starting_position = "";
		while (config_file >> map_name >> map_path >> collision_map_path >> starting_position)
		{
			m_Maps[map_name] = new Map(map_path, scale);
			m_Maps[map_name]->InitPositions(starting_position);
			m_CollisionsMaps[map_name] = new Map(collision_map_path, scale, true);
		}
		config_file.close();
	}
	m_CurrentMap = "Courtyard";
}

void GameState::InitView()
{
	int sprite_scale = m_player.GetSprite().getScale().x;
	// These are the limits for the movement of the camera. If the m_player goes behond, the camera stops moving
	m_LockView["LEFT"] = m_Maps[m_CurrentMap]->GetPosition().x + m_window.getSize().x / 2;
	m_LockView["RIGHT"] = m_Maps[m_CurrentMap]->GetPosition().x + (m_Maps[m_CurrentMap]->GetSize().x * sprite_scale) - (m_window.getSize().x / 2);
	m_LockView["UP"] = m_Maps[m_CurrentMap]->GetPosition().y + m_window.getSize().y / 2;
	m_LockView["DOWN"] = m_Maps[m_CurrentMap]->GetPosition().y + (m_Maps[m_CurrentMap]->GetSize().y * sprite_scale) - (m_window.getSize().y / 2);

	Vector2f sprite_size(m_player.GetSprite().getGlobalBounds().width, m_player.GetSprite().getGlobalBounds().height);

	m_PlayerView.setCenter(m_player.GetSprite().getPosition().x + sprite_size.x / 2, m_player.GetSprite().getPosition().y + sprite_size.y / 2);
}

void GameState::InitGUI(const std::string& player_name)
{
	m_GUI["PLAYER"] = new PlayerGUI(m_window, m_player, player_name);
	m_GUI["MINI_MAP"] = new MiniMapGUI(m_window, m_player , *m_Maps[m_CurrentMap]->GetTexture());
	m_GUI["CHAT_BOX"] = new ChatBoxGUI(m_window, m_player);
	m_GUI["MENU"] = new MenuGUI(m_window);
	m_GUI["INVENTORY"] = new InventoryGUI(m_window);
}

void GameState::ResetView(bool new_map)
{
	Vector2f sprite_size(m_player.GetSprite().getGlobalBounds().width, m_player.GetSprite().getGlobalBounds().height);

	// If the map changes, we have to modify the previous value of m_LockView
	if (new_map)
		InitView();
	else
		m_PlayerView.setCenter(m_player.GetSprite().getPosition().x + sprite_size.x / 2, m_player.GetSprite().getPosition().y + sprite_size.y / 2);

	if (m_PlayerView.getCenter().x < m_LockView["LEFT"])
	{
		m_PlayerView.setCenter(m_LockView["LEFT"], m_PlayerView.getCenter().y);
	}
	else if (m_PlayerView.getCenter().x >= m_LockView["RIGHT"])
	{
		m_PlayerView.setCenter(m_LockView["RIGHT"] - 1, m_PlayerView.getCenter().y);
	}
	if (m_PlayerView.getCenter().y < m_LockView["UP"])
	{
		m_PlayerView.setCenter(m_PlayerView.getCenter().x, m_LockView["UP"]);
	}
	else if (m_PlayerView.getCenter().y >= m_LockView["DOWN"])
	{
		m_PlayerView.setCenter(m_PlayerView.getCenter().x, m_LockView["DOWN"] - 1);
	}
}

bool GameState::CheckSpriteCollision(const float & dt,std::string movement)
{
	// Collision are tested on a copy of the map (m_CollisionsMaps). The areas that can't be crossed by the m_player are in red (255, 0, 0).
	Vector2f sprite_position = Vector2f(m_player.GetSprite().getPosition().x / m_CollisionsMaps[m_CurrentMap]->GetScale(), m_player.GetSprite().getPosition().y / m_CollisionsMaps[m_CurrentMap]->GetScale());
	sprite_position = Vector2f(std::roundl(sprite_position.x), std::roundl(sprite_position.y));

	Vector2f sprite_size = Vector2f(m_player.GetSprite().getGlobalBounds().width / m_CollisionsMaps[m_CurrentMap]->GetScale(), m_player.GetSprite().getGlobalBounds().height / m_CollisionsMaps[m_CurrentMap]->GetScale());

	Color pixel_toward_color[3];

	if (movement == "UP")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y - 1);
		pixel_toward_color[1] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x / 2 , sprite_position.y - 1 + sprite_size.y);
		pixel_toward_color[2] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y - 1 + sprite_size.y);
	}
	else if (movement == "DOWN")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[1] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x / 2, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[2] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y + sprite_size.y + 1);
	}
	else if (movement == "LEFT")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1, std::min(sprite_position.y + sprite_size.y, m_Maps[m_CurrentMap]->GetSize().y));
		// Others are not required
		pixel_toward_color[1] = Color::Black;
		pixel_toward_color[2] = Color::Black;
	}
	else if (movement == "RIGHT")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x + 1, std::min(sprite_position.y + sprite_size.y, m_Maps[m_CurrentMap]->GetSize().y));
		pixel_toward_color[1] = Color::Black;
		pixel_toward_color[2] = Color::Black;
	}
	for (auto &it : pixel_toward_color)
	{
		if (it == Color::Red)
		{
			m_player.GetAnimation().SetSide(StringToSide(movement));
			return true;
		}
		else if (it == Color::Magenta || it == Color::Blue || it == Color::Green || it == Color::Yellow)
		{
			m_CantMove = true;
			m_TransitionColor = it;
			return true;
		}
	}
	return false;
}

void GameState::MovePlayer(const float &dt)
{
	bool running = false;								// Makes the m_player run
	if (Joystick::isButtonPressed(0, m_Actions["RUN"]) || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["RUN"])))
	{
		m_player.GetMovement().SetMaxVelocity(2.f);
		running = true;
	}
	else
		m_player.GetMovement().SetMaxVelocity(1.f);
	Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));

	if (!m_CantMove)
	{
		if (controller_position.y < -80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["UP"])))
		{
			if (!CheckSpriteCollision(dt, "UP"))
			{
				m_player.GetMovement().SetVelocityX(0);
				m_player.Move(dt, 0.f, (running ? -2.f : -1.f));
			}
			else
				m_player.GetAnimation().PlayAnimation(0, dt, "UP");
		}
		else if (controller_position.y > 80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["DOWN"])))
		{
			if (!CheckSpriteCollision(dt, "DOWN"))
			{
				m_player.GetMovement().SetVelocityX(0);
				m_player.Move(dt, 0.f, (running ? 2.f : 1.f));
			}
			else
				m_player.GetAnimation().PlayAnimation(0, dt, "DOWN");
		}
		else if (controller_position.x < -80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["LEFT"])))
		{
			if (!CheckSpriteCollision(dt, "LEFT"))
			{
				m_player.GetMovement().SetVelocityY(0);
				m_player.Move(dt, (running ? -2.f : -1.f), 0.f);
			}
			else
				m_player.GetAnimation().PlayAnimation(0, dt, "LEFT");
		}
		else if (controller_position.x > 80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["RIGHT"])))
		{
			if (!CheckSpriteCollision(dt, "RIGHT"))
			{
				m_player.GetMovement().SetVelocityY(0);
				m_player.Move(dt, (running ? 2.f : 1.f), 0.f);
			}
			else
				m_player.GetAnimation().PlayAnimation(0, dt, "RIGHT");
		}
	}
}

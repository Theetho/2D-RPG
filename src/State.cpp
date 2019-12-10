#include "stdafx.h"
#include "Macros.h"
#include "State.h"
#include "MenuState.h"

using namespace sf;

// Constructor
State::State(RenderWindow& window, std::stack<State*>& states_stack, const WhichState &state, bool &running) :
m_window(window),
m_quit(false),
m_Running(running),
m_MousePosition(0, 0),
m_StatesStack(states_stack), 
m_State(state)
{
	if (m_State != WhichState::MENU_STATE)
	{
		if (Joystick::isConnected(0))
		{
			InitControllerKeys();
			InitControllerActions();
		}
		else
		{
			InitKeyboardKeys();
			InitKeyboardActions();
		}
	}

	sf::Cursor cursor;
	cursor.loadFromSystem(Cursor::Arrow);
	m_window.setMouseCursor(cursor);
}
// Destructor
State::~State()
{}

// Functions
/////////////////////////////////////////////////////////////////////
/// Initializes the key used in the m_State with the parameters in the file right file
/// Format :
///	Key_Name SFML_Key_Value
/////////////////////////////////////////////////////////////////////
void State::InitKeyboardKeys()
{
	m_Keys.clear();

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (m_State)
	{
	case WhichState::GAME_STATE:
		config_file.open("res/config/input/Keyboard/Game/Inputs.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->GetMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("res/config/input/Keyboard/Main_Menu/Inputs.cfg");
			break; 
		case Menu::CHARACTER_MENU:
			config_file.open("res/config/input/Keyboard/Character_Menu/Inputs.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("res/config/input/Keyboard/Pause_Menu/Inputs.cfg");
			break;
		default:
			break;
		}
		break;
	case WhichState::EDITOR_STATE:
		config_file.open("res/config/input/Keyboard/editor/Inputs.cfg");
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			m_Keys[key] = key_value;
		}
		config_file.close();
	}
}

void State::InitControllerKeys()
{
	m_Keys.clear();

	Joystick::Identification id = Joystick::getIdentification(0);
	std::string name = static_cast<std::string>(id.name);
	std::string vendorId = std::to_string(id.vendorId);
	std::string productId = std::to_string(id.productId);

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);

	switch (m_State)
	{
	case WhichState::GAME_STATE:
		config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Game/Inputs.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->GetMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Main_Menu/Inputs.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Character_Menu/Inputs.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Pause_Menu/Inputs.cfg");
			break;
		default:
			break;
		}
		break;
	case WhichState::EDITOR_STATE:
		config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/editor/Inputs.cfg");
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			m_Keys[key] = key_value;
		}
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of m_Actions for each key with the parameters in the files "Game/m_Actions.cfg"
/// Format :
///	Action_Name >> Key_Name
/////////////////////////////////////////////////////////////////////
void State::InitKeyboardActions()
{
	m_Actions.clear();

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (m_State)
	{
	case WhichState::GAME_STATE:
		config_file.open("res/config/input/Keyboard/Game/Actions.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->GetMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("res/config/input/Keyboard/Main_Menu/Actions.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("res/config/input/Keyboard/Character_Menu/Actions.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("res/config/input/Keyboard/Pause_Menu/Actions.cfg");
			break;
		default:
			break;
		}
		break;
	case WhichState::EDITOR_STATE:
		config_file.open("res/config/input/Keyboard/editor/Actions.cfg");
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			m_Actions[action] = m_Keys[key];
		}
		config_file.close();
	}
}

void State::InitControllerActions()
{
	m_Actions.clear();

	Joystick::Identification id = Joystick::getIdentification(0);
	std::string name = static_cast<std::string>(id.name);
	std::string vendorId = std::to_string(id.vendorId);
	std::string productId = std::to_string(id.productId);

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (m_State)
	{
	case WhichState::GAME_STATE:
		config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Game/Actions.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->GetMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Main_Menu/Actions.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Character_Menu/Actions.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/Pause_Menu/Actions.cfg");
			break;
		default:
			break;
		}
		break;
	case WhichState::EDITOR_STATE:
		config_file.open("res/config/input/Controller/" + name + "_" + vendorId + "_" + productId + "/editor/Actions.cfg");
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			m_Actions[action] = m_Keys[key];
		}
		config_file.close();
	}
}

// Getters
const bool& State::GetQuit() const
{
	return m_quit;
}

const WhichState & State::GetState() const
{
	return m_State;
}

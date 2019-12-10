#include "stdafx.h"
#include "Macros.h"
#include "Game.h"

sf::Event Game::s_event;

// Constructor
Game::Game() :
m_DeltaTime(0.0), 
m_Fullscreen(false),
m_Running(true),
m_Music("res/config/music/music.cfg")
{
	InitWindow();
	InitStates();
	if (sf::Joystick::isConnected(0))
		m_window.setMouseCursorVisible(false);
	else
		m_window.setMouseCursorVisible(true);

	m_window.setActive(true);
}
// Destructor
Game::~Game()
{
	// Delete the states stack
	while (!m_States.empty())
	{
		delete m_States.top();
		m_States.pop();
	}
}

// It is the main fonction (this is where the magic happens)
void Game::Run()
{
	// Main loop
	while (m_Running)
	{
		// Update delta time to know how long it takes to do the entire loop
		UpdateDt();
		Update();
		Render();
	}
}

void Game::Update()
{
	m_window.clear();
	
	UpdateEvents();

	// Updates from top state
	if (!m_States.empty())
	{
		UpdateMusic();
		m_States.top()->Update(m_DeltaTime);
		// Pops the state it is finished/closed 
		if (m_States.top()->GetQuit())
		{
			delete m_States.top();
			m_States.pop();
		}
	}
	// There is no more states
	else
	{
		m_Running = false;
	}
}

void Game::UpdateEvents()
{
	while (m_window.pollEvent(s_event))
	{
		if (s_event.type == sf::Event::Closed)
		{
			m_Running = false;
			break;
		}
		else if (s_event.type == sf::Event::JoystickConnected)
		{
			m_States.top()->InitControllerKeys();
			m_States.top()->InitControllerActions();
			m_window.setMouseCursorVisible(false);
		}
		else if (s_event.type == sf::Event::JoystickDisconnected)
		{
			m_States.top()->InitKeyboardKeys();
			m_States.top()->InitKeyboardActions();
			m_window.setMouseCursorVisible(true);
		}
		else if (s_event.type == sf::Event::JoystickMoved)
		{
			if (std::abs(s_event.joystickMove.position) > 80)
				m_States.top()->HandleInput(-1, m_DeltaTime);
		}
		else if (s_event.type == sf::Event::JoystickButtonReleased)
		{
			m_States.top()->HandleInput(s_event.joystickButton.button, m_DeltaTime);
		}
		else if (s_event.type == sf::Event::TextEntered)
		{
			m_States.top()->HandleInput(s_event.key.code, m_DeltaTime);
		}
		else if (s_event.type == sf::Event::KeyReleased)
		{
			m_States.top()->HandleInput(s_event.key.code, m_DeltaTime);
		}
		else if (s_event.type == sf::Event::MouseButtonReleased && m_States.top()->GetState() == WhichState::EDITOR_STATE)
		{
			auto state = static_cast<EditorState*>(m_States.top());
			state->Update(m_DeltaTime, &s_event);
		}
	}
}

void Game::UpdateMusic()
{
	if (m_States.top()->GetState() == WhichState::MENU_STATE)
	{
		MenuState* menu = static_cast<MenuState*>(m_States.top());
		if (menu->GetMenuType() == Menu::PAUSE_MENU)
		{
			m_Music.Pause("GAME");
			m_Music.Play(m_DeltaTime, "PAUSE_MENU");
		}
		else
		{
			m_Music.Stop("PAUSE_MENU");
			m_Music.Stop("GAME");
			m_Music.Play(m_DeltaTime, "MENU");
		}
	}
	else if (m_States.top()->GetState() == WhichState::GAME_STATE)
	{
		m_Music.Stop("PAUSE_MENU");
		m_Music.Stop("MENU");
		m_Music.Play(m_DeltaTime, "GAME");
	}
	else if (m_States.top()->GetState() == WhichState::EDITOR_STATE)
	{
		m_Music.Stop("PAUSE_MENU");
		m_Music.Stop("MENU");
	}
}

void Game::UpdateDt()
{
	m_DeltaTime = m_Clock.restart().asSeconds();
}

void Game::Render()
{
	// Renders from state
	if (!m_States.empty())
	{
		// Render the game under the pause menu 
		if (m_States.top()->GetState() == WhichState::MENU_STATE)
		{
			auto menu = static_cast<MenuState*>(m_States.top());
			if (menu->GetMenuType() == Menu::PAUSE_MENU)
			{
				m_States.pop();
				m_States.top()->Render(m_window);
				m_States.push(menu);
			}
		}
		m_States.top()->Render(m_window);
	}

	//_DisplayFPS();

	m_window.display();
}
/////////////////////////////////////////////////////////////////////
/// Initializes the m_window with the parameters in the file "m_window.cfg" 
/// Format :
/// Title
///	Width Height
///	FullScreen
///	FPS
///	Vertical synchronisation enabled 
/////////////////////////////////////////////////////////////////////
void Game::InitWindow()
{
	std::ifstream config_file("res/config/window/window.cfg");

	std::string title("None");
	sf::ContextSettings contexte;
	sf::VideoMode video_mode(sf::VideoMode::getDesktopMode());
	unsigned fps = 120;
	bool vertical_sync_enabled = false;

	if (config_file.is_open())
	{
		std::getline(config_file, title);
		config_file >> contexte.depthBits >> contexte.stencilBits >> contexte.antialiasingLevel >> contexte.majorVersion >> contexte.minorVersion;
		config_file >> video_mode.width >> video_mode.height;
		config_file >> m_Fullscreen;
		config_file >> fps;
		config_file >> vertical_sync_enabled;
		config_file.close();
	}
	if (m_Fullscreen)
		m_window.create(video_mode, title, sf::Style::Fullscreen, contexte);
	else
		m_window.create(video_mode, title, sf::Style::Close, contexte);

	m_window.setFramerateLimit(fps);
	m_window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::InitStates()
{
	m_States.push(new MenuState(m_window, m_States, WhichState::MENU_STATE, m_Running, "res/config/buttons/main_menu.cfg", Menu::MAIN_MENU));
}

void Game::DisplayFPS()
{
	sf::Font font;
	font.loadFromFile("res/fonts/Animales_Fantastic.otf");

	sf::Text fps;
	fps.setString(std::to_string(static_cast<int>(1 / m_DeltaTime)));
	fps.setCharacterSize(60);
	fps.setFont(font);
	fps.setFillColor(sf::Color::Black);
	m_window.draw(fps);
}


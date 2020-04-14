#include "stdafx.h"
#include "Macros.h"
#include "MenuState.h"

using namespace sf;

// Constructor
MenuState::MenuState(RenderWindow& window, std::stack<State*>& states_stack, WhichState state, bool &running, const std::string path, const Menu menu_type) :
State(window, states_stack, state, running),
m_Type(menu_type), 
m_ActivatedButtons{ nullptr, "" },
m_MovedX(false),
m_MovedY(false)
{
	Joystick::isConnected(0) ? InitControllerKeys() : InitKeyboardKeys(); 
	Joystick::isConnected(0) ? InitControllerActions() : InitKeyboardActions();
	InitFonts();
	InitTitle(path);
	InitButtons(path);

	if (m_Type == Menu::PAUSE_MENU)
	{
		m_Background.setSize(Vector2f(m_window.getSize().x / 2, m_window.getSize().y));
		m_Background.setPosition(m_window.getSize().x / 4, 0);
		m_Background.setFillColor(Color::Transparent);
	}
	else
	{
		m_Background.setSize(Vector2f(m_window.getSize()));
		m_Background.setFillColor(Color(0, 128, 255));
	}

	if (m_Type == Menu::CHARACTER_MENU)
	{
		// Initialize the m_Sprites m_Background
		Color bgColor = Color::Black;
		bgColor.a = 128;
		m_SpritesBackground.setFillColor(bgColor);
		m_SpritesBackground.setPosition(Vector2f(
			m_Buttons["MALE"]->GetPosition().x - m_Buttons["MALE"]->GetSize().x / 2,
			m_Buttons["WARRIOR"]->GetPosition().y - m_Buttons["WARRIOR"]->GetSize().y / 2));
		m_SpritesBackground.setSize(Vector2f(m_window.getSize().x * 0.45, m_window.getSize().y * 0.5));
		InitSprites();
		InitAnimations();
	}
	if (Joystick::isConnected(0))
	{
		m_SelectedButtons = std::make_pair(0, 0);
		m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetHovered(true);
		m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetSelected(true);
	}
	else
		m_SelectedButtons = std::make_pair(-1, -1);
}
// Destructor
MenuState::~MenuState()
{
	for (auto &it : m_Buttons)
		delete it.second;
	for (auto &it : m_Sprites)
		delete it.second;
	for (auto &it : m_SpritesAnimations)
		delete it.second;

	m_Cursor.loadFromSystem(Cursor::Arrow);
	m_window.setMouseCursor(m_Cursor);
}

// Functions
void MenuState::HandleInput(const int &input, const float & dt)
{
	if (m_Type == Menu::CHARACTER_MENU && m_Buttons["PSEUDO"]->GetActivated())	
	{
		auto text_field = static_cast<TextField*>(m_Buttons["PSEUDO"]);
		text_field->HandleInput();
		//if (!Joystick::isConnected(0))
			//input = -1;									// Consumes the input
	}
	// Specific parts
	switch (m_Type)
	{
	case Menu::MAIN_MENU:
		break;
	case Menu::PAUSE_MENU:
		if (input == (Joystick::isConnected(0) ? m_Actions["RESUME"] : Keyboard::Key(m_Actions["RESUME"])))
			m_quit = true;
		break;
	case Menu::CHARACTER_MENU:
		if (input == (Joystick::isConnected(0) ? m_Actions["QUIT"] : Keyboard::Key(m_Actions["QUIT"])))
			m_quit = true;
		break;
	default:
		break;
	}

	if (m_SelectedButtons.first == -1 && m_SelectedButtons.second == -1)
	{
		m_SelectedButtons = std::make_pair(0, 0);
		// Selects the current button
		m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetSelected(true);
		return;
	}

	////////////////////////////////////
	/// Infos about controller : 
	/// PS4 : name : Wireless Controller, vendorID : 1356, productID : 2508
	////////////////////////////////////
	Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));

	// Common parts
	if (input == (Joystick::isConnected(0) ? m_Actions["VALIDATE"] : Keyboard::Key(m_Actions["VALIDATE"])))
	{
		if (m_Buttons.count(m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]))
			m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetPressed(true);
	}
	// Unselects the previous button
	m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetSelected(false);
	
	if ((controller_position.y > 80 && !m_MovedY ) || input == Keyboard::Key(m_Actions["DOWN"]))
	{
		m_MovedY = true;
		if (m_SelectedButtons.second < m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1)
		{
			++m_SelectedButtons.second;
		}
		else
		{
			m_SelectedButtons.second = 0;
		}
	}
	else if ((controller_position.y < -80 && !m_MovedY) || input == Keyboard::Key(m_Actions["UP"]))
	{
		m_MovedY = true;
		if (m_SelectedButtons.second != 0)
		{
			--m_SelectedButtons.second;
		}
		else
		{
			m_SelectedButtons.second = m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1;
		}
	}
	else if ((controller_position.x > 80 && !m_MovedX) || input == Keyboard::Key(m_Actions["RIGHT"]))
	{
		m_MovedX = true;
		
		float index = m_SelectedButtons.second / (m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1);
		
		if (m_SelectedButtons.first != m_ButtonsNaviguator.size() - 1)
		{
			++m_SelectedButtons.first;
		}
		else
		{
			m_SelectedButtons.first = 0;
		}
		
		m_SelectedButtons.second = std::round((m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1)* index);
	}
	else if ((controller_position.x	< -80 && !m_MovedX) || input == Keyboard::Key(m_Actions["LEFT"]))
	{
		m_MovedX = true;
		
		float index = m_SelectedButtons.second / (m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1);
		
		if (m_SelectedButtons.first != 0)
		{
			--m_SelectedButtons.first;
		}
		else
		{
			m_SelectedButtons.first = 0;
		}
		m_SelectedButtons.second = std::round((m_ButtonsNaviguator[m_SelectedButtons.first].size() - 1) * index);
	}
	// Selects the current button
	m_Buttons[m_ButtonsNaviguator[m_SelectedButtons.first][m_SelectedButtons.second]]->SetSelected(true);
}

void MenuState::Update(const float& dt)
{
	m_MousePosition = m_window.mapPixelToCoords(Mouse::getPosition(m_window));
	
	UpdateButtons();

	UpdateCursor();

	if (Joystick::isConnected(0))
	{
		Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));

		if (controller_position.y > -20 && controller_position.y < 20)
			m_MovedY = false;
		if (controller_position.x > -20 && controller_position.x < 20)
			m_MovedX = false;
	}
}

void MenuState::UpdateButtons()
{
	for (auto &it : m_Buttons)
	{
		it.second->Update(m_MousePosition);
		if (it.second->GetPressed())
		{
			// Main Menu
			if (it.first == "NEW_GAME")
			{
				if (it.second->GetSelected())
				{
					it.second->SetSelected(false);
					m_SelectedButtons = std::make_pair(-1, -1);
				}
				it.second->SetPressed(false);
				m_StatesStack.push(new MenuState(m_window, m_StatesStack, WhichState::MENU_STATE, m_Running, "res/config/buttons/choose_character_menu.cfg", Menu::CHARACTER_MENU));
			}
			else if (it.first == "EDITOR")
			{
				it.second->SetPressed(false);
				m_StatesStack.push(new EditorState(m_window, m_StatesStack, WhichState::EDITOR_STATE, m_Running));
			}
			else if (it.first == "QUIT")
			{
				m_Running = false;
			}
			// Pause Menu
			else if (it.first == "RESUME")
			{
				m_quit = true;
			}
			else if (it.first == "MAIN_MENU")
			{
				if (m_Type == Menu::CHARACTER_MENU)
				{
					m_quit = true;
				}
				else
				{
					m_StatesStack.push(new MenuState(m_window, m_StatesStack, WhichState::MENU_STATE, m_Running, "res/config/buttons/Main_menu.cfg", Menu::MAIN_MENU));
				}
			}
			else if (it.first == "SETTINGS")
			{
			}
			// Choose Character Menu
			else if (it.first == "MALE")
			{
				it.second->Activate();
				m_Buttons["FEMALE"]->Deactivate();
				m_Buttons["PSEUDO"]->Deactivate();
				it.second->SetPressed(false);
			}
			else if (it.first == "FEMALE")
			{
				it.second->Activate();
				m_Buttons["MALE"]->Deactivate();
				m_Buttons["PSEUDO"]->Deactivate();
				it.second->SetPressed(false);
			}
			else if (it.first == "WARRIOR" || it.first == "MAGICIAN" || it.first == "HEALER" || it.first == "NINJA" || it.first == "RANGER")
			{
				it.second->Activate();
				m_ActivatedButtons.second = it.first;
				if (m_ActivatedButtons.first && m_ActivatedButtons.first != it.second)
				{
					m_ActivatedButtons.first->Deactivate();
				}
				m_ActivatedButtons.first = it.second;
				m_Buttons["PSEUDO"]->Deactivate();
				it.second->SetPressed(false);
			}
			else if (it.first == "GO")
			{
				// Passing the right sprite's animations
				std::string path_to_sprite;
				if (m_Buttons["MALE"]->GetActivated())
				{
					path_to_sprite = "res/config/character_class/" + m_ActivatedButtons.second + "_MALE.cfg";
				}
				else if (m_Buttons["FEMALE"]->GetActivated())
				{
					path_to_sprite = "res/config/character_class/"+ m_ActivatedButtons.second + "_FEMALE.cfg";
				}

				// Reset the button
				it.second->SetPressed(false);

				// Checking if the player chose a pseudo
				TextField* button = static_cast<TextField*>(m_Buttons["PSEUDO"]);
				if (button->GetTextEntered() == "")
				{
					button->Blink();
				}
				else
				{
					m_StatesStack.push(new GameState(m_window, m_StatesStack, WhichState::GAME_STATE, m_Running, path_to_sprite, m_SpritesScale, button->GetTextEntered(), m_font["ALL"]));
				}

				m_Buttons["PSEUDO"]->Deactivate();
			}
			else if (it.first == "PSEUDO")
			{
				it.second->Activate();
				it.second->SetPressed(false);
			}
		}
	}
}

void MenuState::UpdateCursor()
{
	if (m_Buttons.count("PSEUDO"))
	{
		if (m_Buttons["PSEUDO"]->GetHovered())
		{
			m_Cursor.loadFromSystem(Cursor::Text);
			m_window.setMouseCursor(m_Cursor);
			if (m_Buttons["PSEUDO"]->GetActivated())
				m_window.setMouseCursorVisible(false);
		}
		else
		{
			m_Cursor.loadFromSystem(Cursor::Arrow);
			m_window.setMouseCursorVisible(true);
			m_window.setMouseCursor(m_Cursor);
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				m_Buttons["PSEUDO"]->Deactivate();
			}
		}
	}
}

void MenuState::Render(RenderTarget& target)
{
	target.draw(m_Background);
	target.draw(m_Title);
	RenderButtons(target);
	
	if (m_Type == Menu::CHARACTER_MENU)
	{
		target.draw(m_SpritesBackground);
		RenderSprites(target);
	}
}

void MenuState::RenderButtons(RenderTarget& target)
{
	for (auto &it : m_Buttons)
		it.second->Render(target);
}

void MenuState::RenderSprites(RenderTarget& target)
{
	Vector2f sprite_position;
	// If user selected "male"
	if (m_Buttons["MALE"]->GetActivated())
	{
		// Set the position of the sprite on the left (the first one)
		sprite_position = Vector2f(m_Buttons["MALE"]->GetPosition().x - m_SpritesBackground.getSize().x * 0.07, m_Buttons[m_ActivatedButtons.second]->GetPosition().y);
		// For each sprite
		for (auto &it : m_Sprites)
		{
			// Update its position
			it.second->setPosition(sprite_position);
			// Play the right animation
			m_SpritesAnimations[it.first]->PlayAnimation(1, 0.005, m_ActivatedButtons.second + "_" + it.first + "_MALE");
			// Update the position of the next sprite
			sprite_position.x += 20 * m_SpritesScale;
		}
	}
	// Same if user selects "female"
	else if (m_Buttons["FEMALE"]->GetActivated())
	{
		sprite_position = Vector2f(m_Buttons["FEMALE"]->GetPosition().x - m_SpritesBackground.getSize().x * 0.02, m_Buttons[m_ActivatedButtons.second]->GetPosition().y);
		for (auto &it : m_Sprites)
		{
			it.second->setPosition(sprite_position);
			m_SpritesAnimations[it.first]->PlayAnimation(1, 0.005, m_ActivatedButtons.second + "_" + it.first + "_FEMALE");
			sprite_position.x += 20 * m_SpritesScale;
		}
	}
	// Draw all the m_Sprites
	for (auto &it : m_Sprites)
	{
		target.draw(*it.second);
	}
}

void MenuState::InitFonts()
{
	if (!m_font.count("TITLE"))
	{
		m_font["TITLE"].loadFromFile("res/fonts/harryp__.ttf");
	}
	if (!m_font.count("ALL"))
	{
		m_font["ALL"].loadFromFile("res/fonts/GOTHICB.TTF");
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of m_Buttons with the parameters in the file path
/// Format :
///	--- First line for m_Title ---
///	Name >> x >> y >> w >> h >> "Text"- >> r1 >> g1 >> b1 >> r2 >> b2 >> g2 >> r3 >> g3 >> b3 >> rText >> gText >> bText >> textSize >> navigation_row
///	--> x, y, w, and h in percentage of the m_window size
/////////////////////////////////////////////////////////////////////
void MenuState::InitButtons(const std::string path)
{
	float x_window = m_window.getSize().x, y_window = m_window.getSize().y;

	std::ifstream config_file(path);
	if (config_file.is_open())
	{
		int i = 0;
		int button_type = 0;
		/* Action of the button */
		std::string action = "";
		/* Line in the file */
		std::string line = "";
		/* Coordinates and size of the button */
		float x = 0.0, y = 0.0, w = 0.0, h = 0.0;
		/* Text on the button */
		std::string text = "";
		/* Colors of the button */
		int a = 255;
		Color idle_color = Color::White, hover_color = Color::White, active_color = Color::White;
		/* Size of the text on the button */
		float text_size = 12.0;
		int navigation_row = 0;

		/* Skip the first line */
		std::getline(config_file, line, '\n');

		/* For each buttons of this state */
		while(i < m_NumberButtons)
		{
			/* Get button_type */
			std::getline(config_file, line, ' ');
			button_type = static_cast<int>(std::atoi(line.c_str()));

			/* Get action */
			std::getline(config_file, action, ' ');

			/* Get coordinates*/
			std::getline(config_file, line, ' ');
			x = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			y = static_cast<float>(std::atof(line.c_str())*y_window);

			/* Get size */
			std::getline(config_file, line, ' ');
			w = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			h = static_cast<float>(std::atof(line.c_str())*y_window);
			
			/* Get text */
			std::getline(config_file, text, '-');

			/* Get Idle_Color */
			std::getline(config_file, line, ' ');
			idle_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.b = std::atoi(line.c_str());

			/* Get Hover_Color */
			std::getline(config_file, line, ' ');
			hover_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.b = std::atoi(line.c_str());

			/* Get Active_Color */
			std::getline(config_file, line, ' ');
			active_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.b = std::atoi(line.c_str());

			/* Get Text_size */
			std::getline(config_file, line, ' ');
			text_size = (static_cast<float>(std::atof(line.c_str())*x_window));

			/* Get navigation_row */
			std::getline(config_file, line, '\n');
			navigation_row = static_cast<int>(std::atoi(line.c_str()));

			/* Create the button */
			switch (button_type)
			{
			case 0:
				m_Buttons[action] = new Button(x, y, w, h, text, m_font["ALL"], idle_color, hover_color, text_size);
				break;
			case 1:
				m_Buttons[action] = new TextField(m_window, m_font["ALL"], x, y, w, h, text, idle_color, hover_color, text_size, true);
				break;
			default:
				break;
			}
			if (navigation_row == m_ButtonsNaviguator.size())
			{
				std::vector<std::string> new_row;
				m_ButtonsNaviguator.push_back(new_row);
			}
			m_ButtonsNaviguator[navigation_row].push_back(action);
			i++;
		}
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes @member[m_Title] with the FIRST line in the file path
/// Format :
///	number_of_buttons >> x >> y >> "Title"- >> rText >> gText >> bText >> textSize/ <-- end the line with '/'
///	*** Other lines ***
///	--> x and y in percentage of the m_window size
/////////////////////////////////////////////////////////////////////
void MenuState::InitTitle(const std::string path)
{
	float x_window = m_window.getSize().x, y_window = m_window.getSize().y;

	std::ifstream config_file(path);

	if (config_file.is_open())
	{
		float x, y;
		float text_size;
		std::string title, line = "";
		Color text_color;

		std::getline(config_file, line, ' ');
		m_NumberButtons = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		x = static_cast<float>(std::atof(line.c_str())*x_window);

		std::getline(config_file, line, ' ');
		y = static_cast<float>(std::atof(line.c_str())*y_window);

		std::getline(config_file, title, '-');

		std::getline(config_file, line, ' ');
		text_color.r = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.g = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.b = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_size = std::atof(line.c_str())*x_window;

		m_Title.setFont(m_font["TITLE"]);
		m_Title.setFillColor(text_color);
		m_Title.setCharacterSize(text_size);
		m_Title.setString(title);
		m_Title.setPosition(Vector2f(x, y));
		
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of m_Sprites and the sprite_scale depending on the screen size
/////////////////////////////////////////////////////////////////////
void MenuState::InitSprites()
{
	m_Sprites["LEFT"] = new Sprite();
	m_Sprites["DOWN"] = new Sprite();
	m_Sprites["UP"] = new Sprite();
	m_Sprites["RIGHT"] = new Sprite();

	m_SpritesScale = 4 * m_window.getSize().y / 1080; // Equals to 4 in 1920 x 1080
	for (auto &it : m_Sprites)
	{
		it.second->setScale(m_SpritesScale, m_SpritesScale);
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of Animatins with the parameters in the file "Sprites/Sprites.cfg"
/// Format :
///	animation_component >> animation_key >> texture_sheet_path >> number_of_textures >> width >> height >> animation_timer 
/////////////////////////////////////////////////////////////////////
void MenuState::InitAnimations()
{
	std::ifstream config_file("res/config/sprites/sprites.cfg");

	if (config_file.is_open())
	{
		// Creating Animation for each sprite
		for (auto &it : m_Sprites)
		{
			m_SpritesAnimations[it.first] = new AnimationComponent(*it.second);
		}

		std::string animation_component, animation_key, texture_sheet_path;
		int number_of_textures, width, height;
		float animation_timer;

		while (config_file >> animation_component >> animation_key >> texture_sheet_path >> number_of_textures >> width >> height >> animation_timer)
		{
			// Loads appropriate texture
			Texture *texture_sheet = new Texture;
			texture_sheet->loadFromFile(texture_sheet_path);
			// Add it to the animation component
			m_SpritesAnimations[animation_component]->AddAnimation(animation_key, texture_sheet, number_of_textures, width, height, animation_timer);
		}

		config_file.close();

		// Display the warrior male by default
		m_Buttons["WARRIOR"]->Activate();
		m_Buttons["MALE"]->Activate();
		m_ActivatedButtons.first = m_Buttons["WARRIOR"];
		m_ActivatedButtons.second = "WARRIOR";
	}
}

// Getter
const Menu & MenuState::GetMenuType() const
{
	return m_Type;
}

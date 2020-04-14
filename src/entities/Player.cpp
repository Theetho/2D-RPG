#include "stdafx.h"
#include "Macros.h"
#include "Player.h"

using namespace sf;

// Constructor 
Player::Player(float max_velocity, float x_pos, float y_pos, std::string config_file, std::string name, Font& font, int sprite_scale) :
Entity(),
m_Name(name),
m_font(font),
m_Statistics()
{

	InitSprite();
	m_Sprite->setPosition(Vector2f(x_pos, y_pos));
	m_Sprite->setScale(sprite_scale, sprite_scale);

	InitMovementComponent(max_velocity, 10.f, 9.f);
	InitAnimationComponent(config_file);
	InitName();
	
	// Set the sprite texture to IDLE_DOWN at the beginning
	m_Animation->IdleAnimation(0.05, "DOWN");
}
// Destructor
Player::~Player()
{
	delete m_Sprite;
	delete m_Movement;
	delete m_Animation;
	delete m_Hitbox;
}

//Functions
void Player::Update(const float & dt)
{
	if (m_Sprite && m_Movement)
	{
		// Calls the decelerating phase
		m_Movement->Update(dt, *m_Sprite);
		// Update hitbox
		m_Hitbox->Update();
		if (m_Animation)
		{
			// Sets the accurate texture depending on the sprite orientation
			// If the player moves, it will be changes after so those animations are only played if the player doesn't move
			switch (m_Animation->GetSide())
			{
				case AnimationSide::LEFT:
					m_Animation->IdleAnimation(0.005, "LEFT");
					break;
				case AnimationSide::RIGHT:
					m_Animation->IdleAnimation(0.005, "RIGHT");
					break;
				case AnimationSide::UP:
					m_Animation->IdleAnimation(0.005, "UP");
					break;
				case AnimationSide::DOWN:
					m_Animation->IdleAnimation(0.005, "DOWN");
					break;
				default:
					break;
			}
		}
		m_NameRendered.setPosition(m_Sprite->getPosition() - Vector2f((m_NameRendered.getGlobalBounds().width - m_Sprite->getGlobalBounds().width) / 2, 3 * m_Sprite->getScale().x + m_NameRendered.getGlobalBounds().height));
	}
}

void Player::Render(RenderTarget& target)
{
	Entity::Render(target);
	target.draw(m_NameRendered);
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of music with the parameters in the given file
/// Format : 
/// Key >> path >> number_of_textures >> width >> height >> animation_timer
/////////////////////////////////////////////////////////////////////
void Player::InitAnimationComponent(std::string file_path)
{
	// Calls the superclass Init
	Entity::InitAnimationComponent();

	/*	Loads the textures from a file
		Format : 
			key  path  number_of_frames_in_the_animation  width_of_the_texture_sheet  height  time_between_two_frames */
	std::ifstream config_file(file_path);

	if (config_file.is_open())
	{
		std::string key, path;
		int number_of_textures, width, height;
		float animation_timer;

		while (config_file >> key >> path >> number_of_textures >> width >> height >> animation_timer)
		{
			// Loads appropriate texture
			Texture *texture_sheet = new Texture;
			texture_sheet->loadFromFile(path);
			// Add it to the animation component
			m_Animation->AddAnimation(key, texture_sheet, number_of_textures, width, height, animation_timer);
		}
		config_file.close();
	}
}

void Player::InitName()
{
	m_NameRendered.setFont(m_font);
	m_NameRendered.setFillColor(Color::Black);
	m_NameRendered.setString(m_Name);
	m_NameRendered.setCharacterSize(16);
}


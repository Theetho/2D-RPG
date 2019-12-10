#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_

class AnimationComponent
{
private:
	// Private struct that stores one animation
	struct Animation
	{
		sf::Texture* m_TextureSheet;
		sf::Sprite& m_Sprite;
		// Area of the texture sheet that will be rendered
		sf::IntRect m_CurrentRect;
		// Number of image in the texture sheet
		int m_TextureSize;
		// Time between two frames of the animation 
		float m_FrameDelay;
		// Time spend between last call to this animation
		float m_timer;

		// Constructor
		Animation(sf::Texture* texture_sheet, sf::Sprite& sprite, int texture_size, int width, int height, float frame_delay) :
		m_TextureSheet(texture_sheet), 
		m_Sprite(sprite),
		m_TextureSize(texture_size),
		m_CurrentRect(0, 0, width / texture_size, height),
		m_FrameDelay(frame_delay),
		m_timer(0)
		{}

		// Functions

		void Play(const float & velocity, const float &dt)
		{
			// Updates the m_timer
			// Plays the animation faster if the entity's velocity is greater than 1
			if (std::abs(velocity) < 1 || m_TextureSize <= 4)
				m_timer += dt;
			else
				m_timer += dt * std::abs(velocity);
			
			// If there has been enough time since the last frame
			if (m_timer >= m_FrameDelay)
			{
				// Updates sprite's texture
				m_Sprite.setTexture(*m_TextureSheet, true);
				m_Sprite.setTextureRect(m_CurrentRect);
				
				// Resets m_timer
				m_timer = 0;

				// Moves on to the next frame of the animation
				m_CurrentRect.left += m_CurrentRect.width;

				// And if it was the last one, it goes back to first frame
				if (m_CurrentRect.left == m_CurrentRect.width * m_TextureSize)
				{
					Reset();
				}
			}
		}
		
		void Reset()
		{
			m_CurrentRect.left = 0;
			m_timer = 0;
		}
		// Set the texture to the first of the sprite sheet -> idle
		void Idle(const float &dt)
		{
			m_timer += dt;

			if (m_timer >= m_FrameDelay)
			{
				m_Sprite.setTexture(*m_TextureSheet, true);
				m_Sprite.setTextureRect(sf::IntRect(0, 0, m_CurrentRect.width, m_CurrentRect.height));
			}
		}
	};

public:
	// Constructor
	AnimationComponent(sf::Sprite& sprite);
	// Destructor
	virtual ~AnimationComponent();

	// Functions
	void AddAnimation(const std::string key, sf::Texture* texture_sheet, int texture_size, int width, int height, float frame_delay = 0.5);
	void PlayAnimation(const float & velocity, const float & dt, const std::string animation);
	void ResetAnimation(const std::string animation);
	void IdleAnimation(const float &dt, const std::string animation);

	// Getters
	inline const AnimationSide GetSide() const { return m_Side; }
	inline sf::Texture& GetTexture(const std::string animation) {if (m_Animation.count(animation)) return *m_Animation[animation]->m_TextureSheet; }

	// Setter
	inline void SetSide(const AnimationSide side) { m_Side = side; }

private:
	// Map of animation
	std::map<std::string, Animation*> m_Animation;
	// Sprite on which to play the animation
	sf::Sprite& m_Sprite;
	// Orientation of this sprite (to play the right animation)
	AnimationSide m_Side;
};



#endif // !_ANIMATION_COMPONENT_H_

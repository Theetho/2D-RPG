#ifndef MUSIC_COMPONENT_H
#define MUSIC_COMPONENT_H

class MusicComponent
{
public:
	// Constructor
	MusicComponent(const std::string path);
	// Destructor
	virtual ~MusicComponent();

	// Functions
	void Play(const float &dt, const std::string music_key);
	void Pause(const std::string music_key);
	void Stop(const std::string music_key);

	// Getter 
	inline const std::pair<sf::Music*, float >* GetPlay() const { return m_Playing; }

private:
	// The float parameter is the timer to launch the music
	std::map<std::string, std::pair<sf::Music*, float>> m_Musics;
	// Pointer to the music currently played
	std::pair<sf::Music*, float >* m_Playing;
	// Time between two music
	float m_timer;
	int m_MaxVolume;
	
	// Private functions
	void InitMusics(std::string path);
};

#endif // !MUSIC_COMPONENT_H


#include "stdafx.h"
#include "Macros.h"
#include "MusicComponent.h"

using namespace sf;

// Constructor
MusicComponent::MusicComponent(std::string path) :
m_Playing(nullptr),
m_timer(2.5),
m_MaxVolume(100)
{
	InitMusics(path);
}
// Destructor
MusicComponent::~MusicComponent()
{
	for (auto &it : m_Musics)
		delete it.second.first;
}

// Functions
/////////////////////////////////////////////////////////////////////
/// Initializes the map of music with the parameters in the given file
/// Format : 
/// Key >> path
/////////////////////////////////////////////////////////////////////
void MusicComponent::InitMusics(std::string path)
{
	std::ifstream config_file(path);

	if (config_file.is_open())
	{
		std::string key = "", music_path = "";
		while (config_file >> key >> music_path)
		{
			m_Musics[key].first = new Music();
			m_Musics[key].first->openFromFile(music_path);
			m_Musics[key].first->setVolume(0);
			m_Musics[key].first->setLoop(true);
			m_Musics[key].second = 0;
		}
		config_file.close();
	}
}

void MusicComponent::Play(const float &dt, std::string music_key)
{ 
	if (m_Musics.count(music_key))
	{
		// Updates the timer
		m_Musics[music_key].second += dt;
		// If it is high enough
		if (m_Musics[music_key].second >= m_timer)
		{
			// If this music is not playing
			if (m_Playing != &m_Musics[music_key])
			{
				// If isPlaying is not nullptr
				if (m_Playing)
				{
					// Then it reSets it timer and its sound
					m_Playing->first->setVolume(0);
					m_Playing->second = 0;
				}
				// Change isPlaying pointer
				m_Playing = &m_Musics[music_key];
				// Play the music
				m_Playing->first->play();
			}
			// If this music was playing but was paused
			else if (m_Playing && m_Playing->first->getStatus() == Music::Status::Paused)
			{
				// Resumes it
				m_Playing->first->play();
			}
			// If this music is playing and its volume is not max, then it rises
			else
			{
				if (m_Playing->first->getVolume() < m_MaxVolume)
				{
					m_Playing->first->setVolume(m_Playing->first->getVolume() + 5 * dt);
				}
			}
		}
	}
}

void MusicComponent::Pause(std::string music_key)
{
	if (m_Musics.count(music_key) && m_Playing == &m_Musics[music_key])
		m_Musics[music_key].first->pause();
}

void MusicComponent::Stop(std::string music_key)
{
	if (m_Musics.count(music_key) && m_Playing == &m_Musics[music_key])
		m_Musics[music_key].first->stop();
}

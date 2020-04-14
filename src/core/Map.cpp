#include "stdafx.h"
#include "Macros.h"
#include "Map.h"

// Constructor
Map::Map(const std::string texture_path, int map_scale, bool collision) :
m_Scale(map_scale)
{
	m_MapTexture = new sf::Texture;
	if (m_MapTexture->loadFromFile(texture_path))
	{
		if (collision)
			m_MapImage = m_MapTexture->copyToImage();
		else
		{
			m_Map.setTexture(m_MapTexture);
			m_Map.setPosition(0, 0);
			m_Map.setSize(static_cast<sf::Vector2f>(m_MapTexture->getSize()));
			m_Map.setScale(m_Scale, m_Scale);
		}
	}
	else
	{
		m_Map.setFillColor(sf::Color::Black);
	}

}
// Destructor
Map::~Map()
{
	delete m_MapTexture;
}

// Functions
void Map::Update(const float & dt)
{
}

void Map::Render(sf::RenderTarget& target)
{
	target.draw(m_Map);
}

// Getters
const sf::Color Map::GetPixelColor(int x, int y) const
{
	if (0 <= x && x < m_MapImage.getSize().x && 0 <= y && y < m_MapImage.getSize().y)
		return m_MapImage.getPixel(x, y);
	else
		return sf::Color::Red;
}

const sf::Vector2f Map::GetStartingPosition(std::string key) const
{
	if (m_StartingPositions.count(key))
		return m_StartingPositions.at(key);
}
/////////////////////////////////////////////////////////////////////
/// Initializes the starting position with the parameters in the given file
/// Format :
/// Key >> x >> y;
/////////////////////////////////////////////////////////////////////
void Map::InitPositions(std::string path)
{
	std::ifstream config_file(path);
	if (config_file.is_open())
	{
		std::string key;
		float x, y;

		while (config_file >> key >> x >> y)
		{
			m_StartingPositions[key] = sf::Vector2f(x * m_Scale, y * m_Scale);
		}
		config_file.close();
	}
}


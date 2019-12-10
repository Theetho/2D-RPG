#ifndef MAP_H
#define MAP_H

class Map
{
public:
	// Constructor
	Map(const std::string texture_path, int map_scale = 1, bool collision = false);
	// Destructor
	virtual ~Map();

	// Functions
	void Update(const float & dt);
	void Render(sf::RenderTarget& target);
	void InitPositions(const std::string path);

	// Getters
	inline const sf::Vector2f& GetSize() const { return m_Map.getSize(); }
	inline const sf::Vector2f& GetPosition() const { return m_Map.getPosition(); }
	inline const sf::RectangleShape& GetShape() const { return m_Map; }
	inline const int& GetScale() const { return m_Scale; }
	inline sf::Texture* GetTexture() { return m_MapTexture; }
	const sf::Vector2f GetStartingPosition(const std::string key) const;
	const sf::Color GetPixelColor(int x, int y) const;

	// Setter
	inline void SetScale(int scale) { m_Scale = scale; }

private:
	sf::RectangleShape m_Map;
	sf::Texture* m_MapTexture;
	sf::Image m_MapImage;
	std::map<std::string, sf::Vector2f> m_StartingPositions;
	int m_Scale;
};



#endif // !MAP_H
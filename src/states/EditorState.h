#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "gui/EditorGUI.h"

class EditorState : public State
{
public:
	// Constructor
	EditorState(sf::RenderWindow &window, std::stack<State*> &states_stack, WhichState state, bool &running);
	// Destructor
	~EditorState();

	// Functions
	inline void Update(const float &dt) { Update(dt, nullptr); }
	void Update(const float &dt, sf::Event *event = nullptr);
	void Render(sf::RenderTarget &target);
	void HandleInput(const int &input, const float &dt);

private:
	std::vector<std::pair<sf::Texture*, std::vector<int>>> m_TilesTextureSheets;
	std::vector<sf::RectangleShape> m_Tiles;
	std::vector< std::pair< std::vector<sf::RectangleShape>, int> > m_DrawableTiles;
	sf::RectangleShape m_DrawingArea, m_TileCursor;
	sf::RectangleShape m_SelectedTile;
	EditorGUI m_GUI;
	float m_OffsetLeft;
	int m_TileIndex;
	int m_TilesSize;
	static const float m_TilesScale;
	
	// Private function
	void InitTiles();
	void InitDrawingArea();
};

#endif // !EDITOR_STATE_H

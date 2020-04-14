#include "stdafx.h"
#include "Macros.h"
#include "EditorState.h"
#include "MenuState.h"

using namespace sf;

const float EditorState::m_TilesScale = 1.3;

// Construtor
EditorState::EditorState(RenderWindow& window, std::stack<State*>& states_stack, WhichState state, bool &running) :
State(window, states_stack, state, running),
m_GUI(window),
m_OffsetLeft(0),
m_TileIndex(-1)
{
	InitTiles();
	InitDrawingArea();
}
// Destructor
EditorState::~EditorState()
{
	m_window.setMouseCursorVisible(true);
	for (auto &it : m_TilesTextureSheets)
		delete it.first;
}

// Functions
void EditorState::Update(const float & dt, Event *event)
{
	m_GUI.Update(dt);

	auto mouse_position = m_window.mapPixelToCoords(Mouse::getPosition(m_window));
	// Updating the drawing area
	if (m_DrawingArea.getGlobalBounds().contains(mouse_position))
	{
		m_window.setMouseCursorVisible(true);
		int total_column = m_DrawingArea.getSize().x / m_TilesSize;														// Calculate the total number of column			
		int row_index = (mouse_position.y - m_DrawingArea.getPosition().y) / m_TilesSize;								// Calculate the row and the column index
		int column_index = (mouse_position.x - m_DrawingArea.getPosition().x) / m_TilesSize;							// So we have access to the corresponding drawable_tile 
		m_SelectedTile.setPosition(m_DrawableTiles[column_index + total_column * row_index].first[0].getPosition());	// By doing column_index + total_column * row_index

		if (event && event->type == Event::MouseButtonReleased && event->mouseButton.button == Mouse::Button::Left)
		{
			m_window.setMouseCursorVisible(false);
			m_DrawableTiles[column_index + total_column * row_index].first.push_back(RectangleShape(Vector2f(m_TilesSize, m_TilesSize)));
			Vector2f previous_pos = m_DrawableTiles[column_index + total_column * row_index].first[0].getPosition();
			m_DrawableTiles[column_index + total_column * row_index].first.back() = m_SelectedTile;	// Copying the selected tile on the corresponding drawable_tile 
			m_DrawableTiles[column_index + total_column * row_index].first.back().setPosition(previous_pos);
		}
		else if (event && event->type == Event::MouseButtonReleased && event->mouseButton.button == Mouse::Button::Right)
		{
			m_window.setMouseCursorVisible(false);
			m_DrawableTiles[column_index + total_column * row_index].first.back().setTexture(nullptr);	// Removing the tile on the corresponding drawable_tile
			m_DrawableTiles[column_index + total_column * row_index].first.back().setFillColor(Color::Transparent);
			if (m_DrawableTiles[column_index + total_column * row_index].first.size() > 1)
				m_DrawableTiles[column_index + total_column * row_index].first.pop_back();
		}
	}
	else
	{
		// Updating the tile cursor
		for (auto &it : m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second)
		{
			if (m_Tiles[it].getGlobalBounds().contains(mouse_position))
			{
				m_TileIndex = it;
				m_TileCursor.setPosition(m_Tiles[it].getPosition());
				if (Mouse::isButtonPressed(Mouse::Button::Left))
					m_SelectedTile = m_Tiles[it];
			}
		}
		m_window.setMouseCursorVisible(true);
		m_SelectedTile.setPosition(-m_TilesSize, -m_TilesSize);
	}
}

void EditorState::Render(RenderTarget & target)
{
	m_GUI.Render(target);
	if (m_GUI.GetSelectedTileset() >= 0)
	{
		for (auto &it : m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second)
			target.draw(m_Tiles[it]);
	}
	target.draw(m_DrawingArea);
	for (auto &it : m_DrawableTiles)
	{
		for (auto &ite : it.first)
			target.draw(ite);
	}
	if (m_TileIndex >= 0)
		m_TileCursor.setOutlineColor(Color::Red);
	else 
		m_TileCursor.setOutlineColor(Color::Transparent);
	target.draw(m_TileCursor);
	target.draw(m_SelectedTile);
}

void EditorState::HandleInput(const int &input, const float & dt)
{
	Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));
	
	if (input == m_Actions["PAUSE"])
		m_StatesStack.push(new MenuState(m_window, m_StatesStack, WhichState::MENU_STATE, m_Running, "res/config/buttons/Pause_menu.cfg", Menu::PAUSE_MENU));
	else if (controller_position.y > 80 || (m_Actions.count("DOWN") && input == m_Actions["DOWN"]))
	{
		if (m_GUI.GetSelectedTileset() < m_TilesTextureSheets.size() - 1)
		{
			m_TileIndex -= m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[0];
			m_GUI.SetSelectedShape(m_GUI.GetSelectedTileset() + 1);
			m_TileIndex += m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[0];
		}
	}
	else if (controller_position.y < -80 || (m_Actions.count("UP") && input == m_Actions["UP"]))
	{
		if (m_GUI.GetSelectedTileset() > 0)
		{
			m_TileIndex -= m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[0];
			m_GUI.SetSelectedShape(m_GUI.GetSelectedTileset() - 1);
			m_TileIndex += m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[0];
		}
	}
	else if (controller_position.x > 80 || (m_Actions.count("RIGHT") && input == m_Actions["RIGHT"]))
	{
		if (m_TileIndex < m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second.size() - 1])
			++m_TileIndex;
		else if (m_TileIndex < 0)
			m_TileIndex = 0;
		m_TileCursor.setPosition(m_Tiles[m_TileIndex].getPosition());
		m_SelectedTile = m_Tiles[m_TileIndex];
	}
	else if (controller_position.x < -80 || (m_Actions.count("LEFT") && input == m_Actions["LEFT"]))
	{
		if (m_TileIndex > m_TilesTextureSheets[m_GUI.GetSelectedTileset()].second[0])
			--m_TileIndex;
		else if (m_TileIndex < 0)
			m_TileIndex = 0;
		m_TileCursor.setPosition(m_Tiles[m_TileIndex].getPosition());
		m_SelectedTile = m_Tiles[m_TileIndex];
	}
}


// Private function
void EditorState::InitTiles()
{
	std::ifstream config_file("res/config/editor/tiles_sheets.cfg");

	if (config_file.is_open())
	{
		std::string path = "";
		int id = 0, width = 0, height = 0, tiles_size = 0;
		while (config_file >> width >> height >> tiles_size >> path)
		{
			int row = height / tiles_size;					// Number of tiles in one row
			int column = width / tiles_size;				// Number of tiles in one column
			int current_row = 0;							// X position of the current tile
			int current_column = 0;							// Y position of the current tile
			m_TilesSize = tiles_size * m_TilesScale;
			
			std::vector<int> id_vector;
			Texture* texture = new Texture;
			texture->loadFromFile(path);

			// Creation and positionning of the tiles
			for (unsigned i = 0; i < row; ++i) 
			{	
				for (unsigned j = 0; j < column; ++j)
				{
					id_vector.push_back(id++);																	// Each tile as an "id" (number) between 0 and the total number of tiles
					m_Tiles.push_back(RectangleShape(Vector2f(m_TilesSize, m_TilesSize)));		
					m_Tiles.back().setTexture(texture);
					m_Tiles.back().setTextureRect(IntRect(j * tiles_size, i * tiles_size, tiles_size, tiles_size));
					m_Tiles.back().setPosition(current_column * m_TilesSize + m_window.getSize().x * 0.01,
											   current_row++  * m_TilesSize + m_window.getSize().y * 0.01);		// Passing to the next line
					// If it was the last row, it goes back to the row 0 and passes to the next column
					if ((current_row + 1) * m_TilesSize > m_window.getSize().y)								
					{
						current_row = 0;
						++current_column;
					}
				}
			}
			m_OffsetLeft = std::max<float>(static_cast<float>(m_GUI.GetSize().x + (current_column + 1) * m_TilesSize), m_OffsetLeft);	// Update the offset of the drawing area
			m_TilesTextureSheets.push_back(std::make_pair(texture, id_vector));
		}
		config_file.close();
		m_TileCursor.setSize(Vector2f(m_TilesSize, m_TilesSize));
		m_TileCursor.setFillColor(Color::Transparent);
		m_TileCursor.setOutlineColor(Color::Transparent);
		m_TileCursor.setOutlineThickness(1);

		m_SelectedTile = m_TileCursor;
		m_SelectedTile.setOutlineColor(Color::Red);

		m_GUI.Divide(m_TilesTextureSheets.size());		// Creation of the menu on the left to select your tileset
		for (auto &it : m_Tiles)						// Offsetting the tiles on the right of the menu							
			it.setPosition(it.getPosition() + Vector2f(m_GUI.GetSize().x, 0));
	}

}

void EditorState::InitDrawingArea()
{
	int tiles_w = (m_window.getSize().x * 0.98 - m_OffsetLeft) / m_TilesSize;	// We want the area to be a multiple of the tiles size
	int tiles_h = m_window.getSize().y * 0.98 / m_TilesSize;

	m_DrawingArea.setSize(Vector2f(tiles_w * m_TilesSize, tiles_h * m_TilesSize));
	m_DrawingArea.setPosition(Vector2f(m_OffsetLeft, 0) + Vector2f(m_window.getSize().x * 0.01, m_window.getSize().y * 0.01));
	m_DrawingArea.setFillColor(Color(255, 255, 255, 20));
	m_DrawingArea.setOutlineColor(Color::Red);
	m_DrawingArea.setOutlineThickness(2);

	// Creation the subdivision in the drawing area
	for (unsigned line = 0; line < m_DrawingArea.getSize().y / m_TilesSize; ++line)
	{
		for (unsigned column = 0; column < m_DrawingArea.getSize().x / m_TilesSize; ++column)
		{
			m_DrawableTiles.push_back(std::make_pair(std::vector<RectangleShape>(), 0));
			m_DrawableTiles.back().first.push_back(RectangleShape(Vector2f(m_TilesSize, m_TilesSize)));
			m_DrawableTiles.back().first.back().setPosition(m_DrawingArea.getPosition() + Vector2f(column * m_TilesSize, line * m_TilesSize));
			m_DrawableTiles.back().first.back().setFillColor(Color::Transparent);
		}
	}
}

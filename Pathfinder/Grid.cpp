#include "Grid.hpp"

void Grid::generate()
{
	
	float totalCellSize = m_cellSize;

	float gridWidth = m_columns * totalCellSize + (m_columns - 1) * m_gridGap;
	float gridHeight = m_rows * totalCellSize + (m_rows - 1) * m_gridGap;


	float leftMargin = m_pos.x - (gridWidth / 2.0f) + (m_cellSize / 2.0f);
	float topMargin = m_pos.y - (gridHeight / 2.0f) + (m_cellSize / 2.0f);



	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {

			sf::RectangleShape& cell = m_grid[i][j];
			cell.setSize(sf::Vector2f(m_cellSize, m_cellSize));
			cell.setOrigin(m_cellSize / 2.0f, m_cellSize / 2.0f);
			cell.setPosition(sf::Vector2f(leftMargin + (j * (m_cellSize + m_gridGap)), topMargin + ((m_cellSize + m_gridGap) * i)));
			cell.setOutlineThickness(m_cellOutlineThickness);
			cell.setFillColor(m_cellFillColor);
			cell.setOutlineColor(m_cellOutlineColor);

		}
	}

}

void Grid::initialize()
{
	for (size_t i = 0; i < m_rows; i++) {
		m_grid.push_back(std::vector<sf::RectangleShape>(m_columns, sf::RectangleShape()));
	}
}

void Grid::resetSize()
{
	float totalCellSize = m_cellSize;

	float gridWidth = m_columns * totalCellSize + (m_columns - 1) * m_gridGap;
	float gridHeight = m_rows * totalCellSize + (m_rows - 1) * m_gridGap;


	float leftMargin = m_pos.x - (gridWidth / 2.0f) + (m_cellSize / 2.0f);
	float topMargin = m_pos.y - (gridHeight / 2.0f) + (m_cellSize / 2.0f);



	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {

			sf::RectangleShape& cell = m_grid[i][j];
			cell.setSize(sf::Vector2f(m_cellSize, m_cellSize));
			cell.setOrigin(m_cellSize / 2.0f, m_cellSize / 2.0f);
			cell.setPosition(sf::Vector2f(leftMargin + (j * (m_cellSize + m_gridGap)), topMargin + ((m_cellSize + m_gridGap) * i)));
		}
	}
}



Grid::Grid() :
	m_rows(),
	m_columns(),
	m_cellSize(),
	m_cellOutlineThickness(),
	m_gridGap(),
	m_pos(),
	m_cellFillColor(sf::Color::White),
	m_cellOutlineColor(sf::Color::Red),
	m_grid()
{

}

Grid::Grid(size_t row, size_t column, float cellSize) :
	m_rows(row),
	m_columns(column),
	m_cellSize(cellSize),
	m_cellOutlineThickness(),
	m_gridGap(0.1 * m_cellSize),
	m_pos(),
	m_cellFillColor(sf::Color::White),
	m_cellOutlineColor(sf::Color::Red),
	m_grid()
{
	initialize();
	generate();
}

Grid::Grid(size_t row, size_t column, float cellSize, sf::Vector2f position) :
	m_rows(row),
	m_columns(column),
	m_cellSize(cellSize),
	m_cellOutlineThickness(),
	m_gridGap(0.1 * m_cellSize),
	m_pos(position),
	m_cellFillColor(sf::Color::White),
	m_cellOutlineColor(sf::Color::Red),
	m_grid()
{
	initialize();
	generate();
}

Grid::Grid(size_t row, size_t column, float cellSize, float gridGap) :
	m_rows(row),
	m_columns(column),
	m_cellSize(cellSize),
	m_cellOutlineThickness(),
	m_gridGap(gridGap),
	m_pos(),
	m_cellFillColor(sf::Color::White),
	m_cellOutlineColor(sf::Color::Red),
	m_grid()
{
	initialize();
	generate();
}

Grid::Grid(size_t row, size_t column, float cellSize, float gridGap, sf::Vector2f position) :
	m_rows(row),
	m_columns(column),
	m_cellSize(cellSize),
	m_cellOutlineThickness(),
	m_gridGap(gridGap),
	m_pos(position),
	m_cellFillColor(sf::Color::White),
	m_cellOutlineColor(sf::Color::Red),
	m_grid()
{
	initialize();
	generate();
}


void Grid::render(sf::RenderTarget& canvas)
{
	for (auto& vec : m_grid)
		for (auto& cell : vec)
			canvas.draw(cell);
}

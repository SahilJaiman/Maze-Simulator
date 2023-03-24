#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
class Grid
{
protected:
	size_t m_rows;
	size_t m_columns;

	float m_cellSize;
	float m_cellOutlineThickness;
	float m_gridGap;

	sf::Vector2f m_pos;

	sf::Color m_cellFillColor;
	sf::Color m_cellOutlineColor;

	std::vector<std::vector<sf::RectangleShape>> m_grid;

	void generate();
	void initialize();
	void resetSize();

public:
	Grid();
	Grid(size_t row, size_t column, float cellSize);
	Grid(size_t row, size_t column, float cellSize, sf::Vector2f position);
	Grid(size_t row, size_t column, float cellSize, float gridGap);
	Grid(size_t row, size_t column, float cellSize, float gridGap, sf::Vector2f position);
	virtual void render(sf::RenderTarget& canvas);

	//Setters

	void setCellSize(float cellSize) {
		m_cellSize = cellSize;
		resetSize();
	}

	void setGridGap(float gridGap) {
		m_gridGap = gridGap;
		resetSize();
	}

	void setCellOutlineThickness(float cellOutlineThickness) {
		float maxThickness = m_gridGap / 2.0f;
		m_cellOutlineThickness = cellOutlineThickness > maxThickness ? maxThickness : cellOutlineThickness;
		for (auto& vec : m_grid)
			for (auto& cell : vec)
				cell.setOutlineThickness(m_cellOutlineThickness);
	}

	void setCellFillColor(sf::Color cellFillColor) {
		m_cellFillColor = cellFillColor;
		for (auto& vec : m_grid)
			for (auto& cell : vec)
				cell.setFillColor(m_cellFillColor);

	}

	void setCellOutlineColor(sf::Color cellOutlineColor) {
		m_cellFillColor = cellOutlineColor;
		for (auto& vec : m_grid)
			for (auto& cell : vec)
				cell.setOutlineColor(m_cellOutlineColor);

	}

};


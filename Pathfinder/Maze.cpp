#include "Maze.hpp"

Maze::Maze() :
	m_blockedCellColor(sf::Color(255, 120, 0)),
	m_solutionPathColor(sf::Color::Yellow),
	m_solutionPath()

{
}

Maze::Maze(size_t row, size_t column, float cellSize) :
	Grid(row, column, cellSize),
	m_blockedCellColor(sf::Color(255, 120, 0)),
	m_solutionPathColor(sf::Color::Yellow),
	m_solutionPath()
{
}

Maze::Maze(size_t row, size_t column, float cellSize, sf::Vector2f position) :
	Grid(row, column, cellSize, position),
	m_blockedCellColor(sf::Color(255, 120, 0)),
	m_solutionPathColor(sf::Color::Yellow),
	m_solutionPath()
{
}

Maze::Maze(size_t row, size_t column, float cellSize, float gridGap) :
	Grid(row, column, cellSize, gridGap),
	m_blockedCellColor(sf::Color(255, 120, 0)),
	m_solutionPathColor(sf::Color::Yellow),
	m_solutionPath()
{
}

Maze::Maze(size_t row, size_t column, float cellSize, float gridGap, sf::Vector2f position) :
	Grid(row, column, cellSize, gridGap, position),
	m_blockedCellColor(sf::Color(255, 120, 0)),
	m_solutionPathColor(sf::Color::Yellow),
	m_solutionPath()
{
}




void Maze::animate(float currentTime)
{
	if (!m_start)
		return;

	if (m_solutionPath.empty() == true) {
		std::cout << "Empty Solution Path\n";
		m_start = false;
		return;

	}

	static float offset = 0;

	if (currentTime > offset + m_delay*(!isAnimationCompleted)) {
		if (m_solutionPath[m_currentIndex] == std::pair<int, int>(m_rows - 1, m_columns - 1)) {
			
			isAnimationCompleted = true;
			//m_start = false;

			if (m_loop == true) {
				m_start = true;
				m_currentIndex = 1;
				clearPath();
			}
		}
		else {
			isAnimationCompleted = false;
			size_t i = m_solutionPath[m_currentIndex].first;
			size_t j = m_solutionPath[m_currentIndex].second;

			m_grid[i][j].setFillColor(m_solutionPathColor);
			m_currentIndex++;

		}
		offset = currentTime;
	}

}

void Maze::addSolutionPath(const std::vector<std::pair<int, int>>& solutionPath)
{
	m_solutionPath = solutionPath;
}

void Maze::constructMaze(const std::vector<std::vector<int>>& matrix)
{

	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			if (matrix[i][j] == 0) {
				m_grid[i][j].setFillColor(m_blockedCellColor);
			}
			else{
				m_grid[i][j].setFillColor(m_cellFillColor);
			}
		}

	}
	m_grid[0][0].setFillColor(sf::Color::Red);
	m_grid[m_rows - 1][m_columns - 1].setFillColor(sf::Color::Green);

}

void Maze::render(sf::RenderTarget& canvas)
{
	for (auto& vec : m_grid)
		for (auto& cell : vec)
			canvas.draw(cell);
}

void Maze::reset()
{
	m_currentIndex = 1;
	clearPath();
	m_start = false;

}

void Maze::clearPath()
{

	for (size_t itr = 1; itr < m_solutionPath.size() - 1; itr++) {
		auto pair = m_solutionPath[itr];
		m_grid[pair.first][pair.second].setFillColor(m_cellFillColor);
	}
}

#pragma once
#include"Grid.hpp"
#include<iostream>
class Maze : public Grid
{
private:
	sf::Color m_blockedCellColor;
	sf::Color m_solutionPathColor;

	//Animation

	size_t m_currentIndex = 1;
	float m_delay = 0.0625f;
	bool m_loop = false;
	bool m_start = false;
	bool m_reset = false;


	std::vector<std::pair<int, int>> m_solutionPath;
	void clearPath();

public:
	bool isAnimationCompleted = false;
	Maze();
	Maze(size_t row, size_t column, float cellSize);
	Maze(size_t row, size_t column, float cellSize, sf::Vector2f position);
	Maze(size_t row, size_t column, float cellSize, float gridGap);
	Maze(size_t row, size_t column, float cellSize, float gridGap, sf::Vector2f position);

	void animate(float currentTime);
	void addSolutionPath(const std::vector<std::pair<int, int>>& solutionPath);
	void constructMaze(const std::vector<std::vector<int>>& matrix);
	void render(sf::RenderTarget& canvas);

	void reset();

	void setAnimationDelay(float delay) {
		m_delay = delay;
	}

	void setLoop(bool isLoop) {
		m_loop = isLoop;
	}

	void startAnimation(bool start) {
		m_start = start;
	}

	float& getAnimationDelay() {
		return m_delay;
	}

	size_t getCurrentIndex() {
		return m_currentIndex;
	}
};


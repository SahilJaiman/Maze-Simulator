#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stack>

#include "Random.h"

void printMatrix(std::vector<std::vector<int>>& mat);

std::string getMatrixString(std::vector<std::vector<int>>& mat);



namespace maze
{
	struct Node
	{
		int x;
		int y;

		Node(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	class maze_generator_dfs
	{
	private:

		int m_rows;
		int m_columns;
		std::stack<Node> m_stack;
		std::vector<std::vector<int>> m_maze;

		bool validNextNode(Node node);
		void randomlyAddNodesToStack(std::vector<Node> nodes);
		std::vector<Node> findNeighbors(Node node);
		bool pointOnGrid(int x, int y);
		bool pointNotCorner(Node node, int x, int y);
		bool pointNotNode(Node node, int x, int y);

	public:
		maze_generator_dfs(int rows, int columns);
		void generateMaze();
		std::vector<std::vector<int>>& getMaze();



	};


}




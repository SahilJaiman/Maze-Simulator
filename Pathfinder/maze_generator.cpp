#include "maze_generator.hpp"


void printMatrix(std::vector<std::vector<int>>& mat)
{
	size_t row = mat.size();
	size_t col = mat.size() > 0 ? mat.at(0).size() : 0;

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
			std::cout << mat[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

std::string getMatrixString(std::vector<std::vector<int>>& mat)
{
	std::string matrix = "";
	size_t row = mat.size();
	size_t col = mat.size() > 0 ? mat.at(0).size() : 0;
	size_t k = 1;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
				matrix += std::to_string(mat[i][j]) + "  ";
		}

		matrix += "\n";
	}
	matrix += "\n";

	return matrix;
}


maze::maze_generator_dfs::maze_generator_dfs(int rows, int columns) :
	m_rows(rows),
	m_columns(columns),
	m_stack(),
	m_maze()
{
	for (size_t i = 0; i < rows; i++)
		m_maze.push_back(std::vector<int>(columns, 0));
}

void maze::maze_generator_dfs::generateMaze()
{

	m_stack.push(Node(0, 0));
	while (!m_stack.empty()) {

		Node next = m_stack.top();
		m_stack.pop();
		if (validNextNode(next)) {
			m_maze[next.y][next.x] = 1;
			std::vector<Node> neighbors = findNeighbors(next);
			randomlyAddNodesToStack(neighbors);
		}
	}

}

bool maze::maze_generator_dfs::validNextNode(Node node)
{
	int numNeighboringOnes = 0;
	for (int y = node.y - 1; y < node.y + 2; y++) {
		for (int x = node.x - 1; x < node.x + 2; x++) {
			if (pointOnGrid(x, y) && pointNotNode(node, x, y) && m_maze[y][x] == 1) {
				numNeighboringOnes++;
			}
		}
	}
	return (numNeighboringOnes < 3) && m_maze[node.y][node.x] != 1;
}

void maze::maze_generator_dfs::randomlyAddNodesToStack(std::vector<Node> nodes)
{
	int targetIndex;
	while (!nodes.empty()) {
		targetIndex = random.randomInteger(0, int(nodes.size()) - 1);

		m_stack.push(nodes.at(targetIndex));
		auto itr = nodes.begin();
		std::advance(itr, targetIndex);
		nodes.erase(itr);

	}
}

std::vector<maze::Node> maze::maze_generator_dfs::findNeighbors(Node node)
{
	std::vector<Node> neighbors;
	for (int y = node.y - 1; y < node.y + 2; y++) {
		for (int x = node.x - 1; x < node.x + 2; x++) {
			if (pointOnGrid(x, y) && pointNotCorner(node, x, y)
				&& pointNotNode(node, x, y)) {
				neighbors.push_back(Node(x, y));
			}
		}
	}
	return neighbors;
}

bool maze::maze_generator_dfs::pointOnGrid(int x, int y)
{
	return x >= 0 && y >= 0 && x < m_rows&& y < m_columns;
}

bool maze::maze_generator_dfs::pointNotCorner(Node node, int x, int y)
{
	return (x == node.x || y == node.y);
}

bool maze::maze_generator_dfs::pointNotNode(Node node, int x, int y)
{
	return !(x == node.x && y == node.y);
}

std::vector<std::vector<int>>& maze::maze_generator_dfs::getMaze()
{
	return m_maze;
}

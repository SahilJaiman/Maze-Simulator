#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;



void printSolutionPath(const std::vector<std::pair<int, int>>& solutionPath)
{
	for (auto& pr : solutionPath)
		std::cout << "(" << pr.first << "," << pr.second << ")->";
}

std::string getSolutionPathString(const std::vector<std::pair<int, int>>& solutionPath) {

	std::string solutionPathStr="";
	for (size_t i = 0; i < solutionPath.size(); i++)
	{
		if (i < solutionPath.size() - 1) {
			auto pair1 = solutionPath[i];
			auto pair2 = solutionPath[i + 1];
			solutionPathStr += "(" + std::to_string(pair1.first) + "," + std::to_string(pair1.second) + ") -> ";
			solutionPathStr += "(" + std::to_string(pair2.first) + "," + std::to_string(pair2.second) + ")\n";
		}
	}
	solutionPathStr += "\n";
	return solutionPathStr;
}



// Defining hash Function for pair<T1, T2>
struct hash_pair
{
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};
class MazePathFinding
{
public:
	vector<vector<int>> maze;
	int row = maze.size();
	int col = maze.size() > 0 ? maze.at(0).size() : 0;
	unordered_map<pair<int, int>, bool, hash_pair> visited;

	// Defining some constants
	const string DOWN = "down";
	const string RIGHT = "right";
	const string UP = "up";
	const string LEFT = "left";
	const int BLOCK = 1;

	MazePathFinding(const vector<vector<int>>& maze)
	{
		this->maze = maze;
		row = maze.size();
		col = maze.at(0).size();
	}

	// finding the start index

	// Utility Function to check of "O" or "E" ('O' means BLOCK and 'E' means END)
	bool check_for_O_or_E(vector<vector<int>>& maze, string next_move, pair<int, int> current_index)
	{
		bool isPossible = false;
		if (next_move == DOWN)
		{
			if (maze[current_index.first + 1][current_index.second] == 1 || (current_index.first + 1 == row - 1 && current_index.second == col - 1))
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (maze[current_index.first][current_index.second + 1] == 1 || (current_index.first == row - 1 && current_index.second + 1 == col - 1))
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (maze[current_index.first - 1][current_index.second] == 1 || (current_index.first - 1 == row - 1 && current_index.second == col - 1))
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (maze[current_index.first][current_index.second - 1] == 1 || (current_index.first == row - 1 && current_index.second - 1 == col - 1))
				isPossible = true;
		}
		return isPossible;
	}
	// Utility function to check in the hash table if a particular BLOCK is visited or not
	bool isVisited(pair<int, int> current_index, string next_move)
	{
		bool isPossible = false;
		if (next_move == DOWN)
		{
			if (visited[{current_index.first + 1, current_index.second}])
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (visited[{current_index.first, current_index.second + 1}])
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (visited[{current_index.first - 1, current_index.second}])
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (visited[{current_index.first, current_index.second - 1}])
				isPossible = true;
		}
		return isPossible;
	}

	// Utility function for above 2 utility functions (combining above two conditions)
	bool combined_check(vector<vector<int>>& maze, pair<int, int> current_index, string next_move)
	{
		bool isPossible = false;
		if (next_move == DOWN)
		{
			if (current_index.first + 1 < maze.size() && check_for_O_or_E(maze, DOWN, current_index) && !isVisited(current_index, DOWN))
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (current_index.second + 1 < maze[0].size() && check_for_O_or_E(maze, RIGHT, current_index) && !isVisited(current_index, RIGHT))
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (current_index.first - 1 >= 0 && check_for_O_or_E(maze, UP, current_index) && !isVisited(current_index, UP))
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (current_index.second - 1 >= 0 && check_for_O_or_E(maze, LEFT, current_index) && !isVisited(current_index, LEFT))
				isPossible = true;
		}
		return isPossible;
	}

	// Moving the current_index to the next Fesable Block
	pair<int, int> next_fesable_move(vector<vector<int>>& maze, pair<int, int> current_index)
	{
		int rows = maze.size();
		int columns = maze[0].size();
		if (combined_check(maze, current_index, DOWN))
		{

			current_index.first += 1;
		}
		else if (combined_check(maze, current_index, RIGHT))
		{

			current_index.second += 1;
		}
		else if (combined_check(maze, current_index, UP))
		{

			current_index.first -= 1;
		}
		else if (combined_check(maze, current_index, LEFT))
		{

			current_index.second -= 1;
		}
		return current_index;
	}

	// Utility Fuction to check if the next move is Fesable or not
	bool ifNextMovePossible(vector<vector<int>>& maze, pair<int, int> current_index)
	{
		bool is_fesable = false;

		if (combined_check(maze, current_index, DOWN))
		{
			is_fesable = true;
		}
		else if (combined_check(maze, current_index, RIGHT))
		{

			is_fesable = true;
		}
		else if (combined_check(maze, current_index, UP))
		{

			is_fesable = true;
		}
		else if (combined_check(maze, current_index, LEFT))
		{

			is_fesable = true;
		}
		else
			is_fesable = false;
		return is_fesable;
	}

	// Depth First Search Function combining all the above utility function
	// to return a stack of possible moves
	stack<pair<int, int>> depth_first_search()
	{

		pair<int, int> start_index(std::pair<int, int>(0, 0));
		pair<int, int> current_index = start_index;
		stack<pair<int, int>> st;
		// pushing the start_index
		st.push(start_index);
		// setting the start_index as visited
		visited[start_index] = true;

		while (current_index.first != row - 1 || current_index.second != col - 1)
		{

			// if Next move is possible then move the current_index to next fesable block
			// and update the stack and hashtable accordingly
			if (ifNextMovePossible(maze, current_index))
			{
				current_index = next_fesable_move(maze, current_index);
				visited[current_index] = true;
				st.push(current_index);
			}
			// If there is on fesable move, then backtrack to the last last index
			// and set it to the current_index
			else if (!ifNextMovePossible(maze, current_index))
			{

				// pair<int, int> temp = st.top();


				st.pop();

				current_index = st.top();
			}
		}
		// finally after doing the DFS the final stack will contain all the possible moves to reach the END point
		return st;
	}

	std::vector<std::pair<int, int>> getSolutionPath() {

		std::vector<std::pair<int, int>> solutionPath;
		stack<pair<int, int>> path = depth_first_search();
		while (!path.empty())
		{
			solutionPath.push_back(path.top());
			path.pop();
		}
		std::reverse(solutionPath.begin(), solutionPath.end());
		return solutionPath;
	}

	void printPath()
	{

		stack<pair<int, int>> path = depth_first_search();
		vector<pair<int, int>> vt;
		while (!path.empty())
		{
			vt.push_back(path.top());
			path.pop();
		}
		for (int i = vt.size() - 1; i >= 0; i--)
		{
			cout << '(' << vt[i].first << ", " << vt[i].second << ')' << " -> ";
		}
		cout << endl;
	}


};


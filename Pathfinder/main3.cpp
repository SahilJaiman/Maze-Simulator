

/*
	Imgui (Immediate Mode GUI)
	Library for GUI implementation
*/


#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

/*
	Sfml(Simple and Fast Multimedia Library)
	Used for window creation and Rendering
*/

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



//Standard C++ Libraries
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <chrono>

#include "maze_solver.hpp"
#include "maze_solver_dfs.hpp"
#include "maze_generator_dfs.hpp"
#include "Grid.hpp"
#include "Maze.hpp"



#define watch(x) std::cout << (#x) << " is " << (x) << std::endl

//Macro for Converting degree to radian
#define degtorad 0.01745329251

using namespace std;



int main()
{
	srand(time(0));
	//Creating Window//
	sf::Vector2f resolution;

	resolution.x = 1280;
	resolution.y = 720;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Pathfinder", sf::Style::Default, settings);

	ImGui::SFML::Init(window, false);
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/Font/arial.ttf", 16.f);
	ImGui::SFML::UpdateFontTexture();

	//View
	sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));



	

	//Clock
	sf::Clock deltaClock;
	sf::Clock clock;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	float wait = 0.0f;

	sf::Vector2f zoomFactor(1.0, 1.0);


	//Maze Solving
	bool solved = false;

	std::vector<std::pair<int, int>> solutionPath;
	MazePathFinding mpf(mat);

	stack<pair<int, int>> path = mpf.depth_first_search();
	while (!path.empty())
	{
		solutionPath.push_back(path.top());
		path.pop();
	}

	std::reverse(solutionPath.begin(), solutionPath.end());

	grid.addSolutionPath(solutionPath);
	grid.setAnimationDelay(0.0625f);
	grid.setLoop(1);

	

	grid.startAnimation(1);

	//Main Loop
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		totalTime += deltaTime;
		//Event Handling//
		sf::Event event;

		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				zoomFactor.x -= 0.5 * deltaTime;
				view.zoom(zoomFactor.x);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				zoomFactor.y += 0.5 * deltaTime;
				view.zoom(zoomFactor.y);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				view.move(-5.0f, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				view.move(5.0f, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				view.move(0, -5.0f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				view.move(0, +5.0f);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

			}

		}
		ImGui::SFML::Update(window, deltaClock.restart());

		if (totalTime > wait + 0.06250f)
		{
			wait = totalTime;
		}

		grid.animate(totalTime);

		//Clear Video Buffer
		window.clear({ 28,28,28 });

		//Draw
		window.setView(view);

		grid.render(window);
		window.setView(window.getDefaultView());
		ImGui::SFML::Render(window);

		//Render Window
		window.display();

	}

	return 0;
}
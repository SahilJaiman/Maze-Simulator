

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
#include <memory>


#include "maze_solver.hpp"
#include "maze_generator.hpp"
#include "Grid.hpp"
#include "Maze.hpp"
#include "Utility.hpp"


#define watch(x) std::cout << (#x) << " is " << (x) << std::endl

#define overlayWindowFlags  ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav| ImGuiWindowFlags_NoMove



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
	io.Fonts->AddFontFromFileTTF("res/Font/arial.ttf", 16.0f);
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


	// Matrix

	float cellSize = 36.0f;
	float gridGap = 0.5f;
	int dimension = 16;
	int inputDimension = dimension;
	int inputCellSize = cellSize;
	sf::Vector2f mazePos(window.getSize().x / 2u, window.getSize().y / 2u);

	std::shared_ptr<maze::maze_generator_dfs> gen_ptr(new maze::maze_generator_dfs(dimension, dimension));
	gen_ptr->generateMaze();
	auto mazeMatrix = gen_ptr->getMaze(); 

	//Maze
	std::shared_ptr<Maze> maze_ptr(new Maze(dimension, dimension, cellSize, gridGap, mazePos));
	maze_ptr->constructMaze(mazeMatrix);
	maze_ptr->setAnimationDelay(0.0625f);

	//Maze Solving
	std::shared_ptr<MazePathFinding> solver_ptr(new MazePathFinding(mazeMatrix));
	auto solutionPath = solver_ptr->getSolutionPath();
	maze_ptr->addSolutionPath(solutionPath);

	bool showSolutionPathWindow = false;
	bool showBooleanMatrixWindow = false;

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

		}
		ImGui::SFML::Update(window, deltaClock.restart());

		if (ImGui::Begin("Maze"))
		{
			ImGui::InputInt("Dimension", &inputDimension);
			if(ImGui::InputInt("Cell Size", &inputCellSize))
			{
				if (inputCellSize > 0) {
					cellSize = static_cast<float>(inputCellSize);
					maze_ptr->setCellSize(cellSize);
				}
			}
			if (ImGui::InputFloat("Grid Gap", &gridGap, 0.05f, 1.0f))
			{
				if (gridGap >= 0)
					maze_ptr->setGridGap(gridGap);

			}
			if (ImGui::Button("Generate"))
			{
				dimension = inputDimension;
				if (dimension > 1) {

					maze_ptr->reset();
					maze_ptr = std::shared_ptr<Maze>(new Maze(dimension, dimension, cellSize, gridGap, mazePos));
					gen_ptr = std::shared_ptr<maze::maze_generator_dfs>(new maze::maze_generator_dfs(dimension, dimension));
					gen_ptr->generateMaze();
					mazeMatrix = gen_ptr->getMaze();
					maze_ptr->constructMaze(mazeMatrix);
					solver_ptr = std::shared_ptr<MazePathFinding>(new MazePathFinding(gen_ptr->getMaze()));
					solutionPath = solver_ptr->getSolutionPath();
					maze_ptr->addSolutionPath(solutionPath);
				}
			}
			ImGui::Separator();
			if (ImGui::Button("Solve"))
			{
				maze_ptr->startAnimation(1);
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop"))
			{
				maze_ptr->startAnimation(0);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset"))
			{
				maze_ptr->reset();
			}
			ImGui::Spacing();

			if (ImGui::Button("Randomized"))
			{

				maze_ptr->startAnimation(false);
				gen_ptr = std::shared_ptr<maze::maze_generator_dfs>(new maze::maze_generator_dfs(dimension, dimension));
				gen_ptr->generateMaze();
				mazeMatrix = gen_ptr->getMaze();
				maze_ptr->constructMaze(mazeMatrix);
				solver_ptr = std::shared_ptr<MazePathFinding>(new MazePathFinding(gen_ptr->getMaze()));
				solutionPath = solver_ptr->getSolutionPath();
				maze_ptr->addSolutionPath(solutionPath);
				maze_ptr->reset();
			}
			ImGui::Spacing();

			ImGui::SliderFloat("Delay", &maze_ptr->getAnimationDelay(), 0.00f, 1.0f, "%.4f sec");
			ImGui::Separator();
			ImGui::Checkbox("Show Solution Path", &showSolutionPathWindow);
			ImGui::Checkbox("Show Boolean Matrix", &showBooleanMatrixWindow);
			ImGui::End();
		}
		if (showSolutionPathWindow) {
			if (ImGui::Begin("Solution Path", &showSolutionPathWindow))
			{
				
				auto paths = split_string_by_newline(getSolutionPathString(solutionPath));
				for (size_t i = 0; i < solutionPath.size(); i++) {
					
					ImGui::Selectable(paths[i].c_str(), (maze_ptr->getCurrentIndex() - 1 == i));
					
				}
				ImGui::End();
				
			}

		}
		if (showBooleanMatrixWindow) {
	
			if (ImGui::Begin("Boolean Matrix", &showBooleanMatrixWindow, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::TextColored({255,255,255,255}, "%s", getMatrixString(mazeMatrix).c_str());
				ImGui::End();
			}
		}

		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos;
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (work_pos.x + work_size.x - PAD);
		window_pos.y = (work_pos.y + PAD);

		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.35f);
		if (ImGui::Begin("Example: Simple overlay", (bool*)0, overlayWindowFlags))
		{
			ImGui::PushButtonRepeat(true);
			if (ImGui::Button("+", ImVec2(25.0f, 25.0f)))
			{
				zoomFactor.x -= 0.25 * deltaTime;
				view.zoom(zoomFactor.x);
			}
			if (ImGui::Button("-", ImVec2(25.0f, 25.0f)))
			{
				zoomFactor.y += 0.25 * deltaTime;
				view.zoom(zoomFactor.y);
			}
			ImGui::PopButtonRepeat();
			ImGui::End();
		}



		maze_ptr->animate(totalTime);

		//Clear Video Buffer
		window.clear({ 28,28,28 });

		//Draw
		window.setView(view);

		maze_ptr->render(window);
		window.setView(window.getDefaultView());
		ImGui::SFML::Render(window);

		//Render Window
		window.display();

	}

	return 0;
}
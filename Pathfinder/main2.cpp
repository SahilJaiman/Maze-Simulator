

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

#define watch(x) std::cout << (#x) << " is " << (x) << std::endl
//Macro for Converting degree to radian
#define degtorad 0.01745329251

using namespace std;


bool isContainMouse(const sf::RectangleShape& rect, const sf::RenderWindow& window) {
	sf::IntRect bound(rect.getPosition().x, rect.getPosition().y, rect.getGlobalBounds().width,
		rect.getGlobalBounds().height);
	if (bound.contains(sf::Mouse::getPosition(window))) {
		return true;
	}
	return false;
}


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



	// Matrix

	int mat[100] = {
			  1, 0, 1, 1, 1, 1, 0, 1, 1, 1 ,
			  1, 0, 1, 0, 1, 1, 1, 0, 1, 1 ,
			  1, 1, 1, 0, 1, 1, 0, 1, 0, 1 ,
			  0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ,
			  1, 1, 1, 0, 1, 1, 1, 0, 1, 0 ,
			  1, 0, 1, 1, 1, 1, 0, 1, 0, 0 ,
			  1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
			  1, 1, 1, 1, 1, 1, 0, 1, 1, 1 ,
			  1, 1, 0, 0, 0, 1, 1, 1, 0, 1 };


	//Grid

	std::vector<sf::RectangleShape> cubes;
	size_t row = 16;
	size_t col = 32;
	float cubeSize = 32.0f;
	float offset = 0.50f;
	float leftMargin = ((window.getSize().x - (col * cubeSize + col * offset)) / 2.0f) + cubeSize / 2;
	float rightMargin = leftMargin;

	float topMargin = ((window.getSize().y - (row * cubeSize + row * offset)) / 2.0f) + cubeSize / 2;
	watch(leftMargin);
	watch(topMargin);




	cubes.resize(row * col);
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			cubes[col * i + j].setSize({ cubeSize,cubeSize });
			cubes[col * i + j].setOrigin(cubes[col * i + j].getSize().x / 2, cubes[col * i + j].getSize().y / 2);
			cubes[col * i + j].setPosition({ leftMargin + (j * (cubeSize + offset)),topMargin + ((cubeSize + offset) * i) });

			cubes[col * i + j].setOutlineThickness(0.0f);
			cubes[col * i + j].setOutlineColor(sf::Color(255, 0, 0));
			//if (mat[col * i + j] == 0)
				//cubes[col * i + j].setFillColor(sf::Color(0, 0, 0));
			//if (mat[col * i + j] == 1)
			cubes[col * i + j].setFillColor(sf::Color(255, 255, 255));
		}

	}

	cubes[0].setFillColor(sf::Color(255, 0, 0));
	cubes[(row * col) - 1].setFillColor(sf::Color(0, 255, 0));




	//Clock
	sf::Clock deltaClock;
	sf::Clock clock;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	float wait = 0.0f;

	sf::Vector2f zoomFactor(1.0, 1.0);

	size_t currCube = 1;

	//






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

		if (totalTime > wait + 0.25f)
		{
			if (currCube == (row * col) - 1)
			{
				currCube = 1;
			}

			else
			{
				for (size_t i = 0; i < row; i++)
				{
					for (size_t j = 0; j < col; j++)
					{
						size_t k = col * i + j;
						if (k != 0 && k != (row * col) - 1 && k != currCube)
						{
							//if (mat[col * i + j] == 0)
								//cubes[col * i + j].setFillColor(sf::Color(0, 0, 0));
							//if (mat[col * i + j] == 1)
							//cubes[col * i + j].setFillColor(sf::Color(255, 255, 255));
						}


					}

				}
				//if (mat[currCube] == 1)
				//cubes[currCube].setFillColor(sf::Color(0, 0, 255));
				//currCube++;
			}





			wait = totalTime;
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				size_t k = col * i + j;
				if (isContainMouse(cubes[k], window) == true)
				{
					cubes[col * i + j].setFillColor(sf::Color(0, 0, 0));
				}

			}

		}

		



		//Clear Video Buffer
		window.clear({ 28,28,28 });

		//Draw
		window.setView(view);


		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				window.draw(cubes[col * i + j]);

			}

		}
		window.setView(window.getDefaultView());
		ImGui::SFML::Render(window);

		//Render Window
		window.display();

	}

	return 0;
}
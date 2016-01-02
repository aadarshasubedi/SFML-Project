#include "game.h"

#include <iostream>

Game::Game() :
	window_(sf::VideoMode(800, 600), "Test"),
	texture_(),
	player_()
{
	window_.setVerticalSyncEnabled(true);
	if (!texture_.loadFromFile("assets/player.png"))
	{
		std::cout << "Could not load texture from file" << std::endl;
	}
	player_.setTexture(texture_);
	player_.setPosition(100.f, 100.f);
}

void Game::Run(int fps)
{
	sf::Clock clock;
	sf::Time  elapsedTime;
	sf::Time  timePerFrame = sf::seconds(1.f / fps); // 16.7ms per frame

	while (window_.isOpen())
	{
		ProcessEvents();

		elapsedTime = clock.restart();
		while (elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;
			Update(timePerFrame);
		}
		Update(elapsedTime);

		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
		/*else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window_.close();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				player_.isMoving = true;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				player_.rotation = -1;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				player_.rotation = 1;
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				player_.isMoving = false;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				player_.rotation = 0;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				player_.rotation = 0;
			}
		}*/
	}
}

void Game::Update(sf::Time deltaTime)
{
}

void Game::Render()
{
	window_.clear();
	window_.draw(player_);
	window_.display();
}

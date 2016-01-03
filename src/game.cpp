#include "Game.h"

Game::Game()
	: window_(sf::VideoMode(800, 400), "Game", sf::Style::Close)
	, world_(window_)
{
	window_.setVerticalSyncEnabled(true);
}

void Game::Run(int fps)
{
	sf::Clock clock;
	sf::Time  elapsedTime;
	sf::Time  timePerFrame = sf::seconds(1.0f / fps); // 16.7ms per frame

	while (window_.isOpen())
	{
		elapsedTime = clock.restart();

		while (elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;

			ProcessEvents();
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
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				HandleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandleInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				window_.close();
				break;
		}
	}
}

void Game::Update(sf::Time delta)
{
	world_.Update(delta);
}

void Game::Render()
{
	window_.clear();

	world_.Draw();

	//window_.setView(window_.getDefaultView());

	window_.display();
}

void Game::HandleInput(sf::Keyboard::Key key, bool isPressed)
{
}

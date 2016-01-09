#include "Game.h"

Game::Game()
	: window_(sf::VideoMode(800, 400), "Game", sf::Style::Close)
	, world_(window_)
	, font_()
	, statisticsText_()
	, statisticsUpdateTime_()
	, statisticsNumFrames_(0)
{
	window_.setVerticalSyncEnabled(true);

	font_.loadFromFile("assets/arial.ttf");
	statisticsText_.setFont(font_);
	statisticsText_.setPosition(5.f, 5.f);
	statisticsText_.setCharacterSize(10);
	statisticsText_.setFillColor(sf::Color::Black);
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time updateTime = sf::Time::Zero;
	sf::Time  spf = sf::seconds(0.016666666667f); // 60 fps

	while (window_.isOpen())
	{
		sf::Time dt = clock.restart();
		updateTime += dt;

		while (updateTime > spf)
		{
			updateTime -= spf;

			ProcessInput();
			Update(spf);
		}

		UpdateStatistics(dt);

		Render();
	}
}

void Game::ProcessInput()
{
	CommandQueue & commands = world_.getCommandQueue();

	sf::Event event;
	while (window_.pollEvent(event))
	{
		player_.HandleEvent(event, commands);

		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
	}

	player_.HandleInput(commands);
}

void Game::Update(sf::Time delta)
{
	world_.Update(delta);
}

void Game::Render()
{
	window_.clear();

	world_.Draw();
	window_.setView(window_.getDefaultView());
	window_.draw(statisticsText_);

	window_.display();
}

void Game::HandleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (!isPressed && key == sf::Keyboard::Escape)
	{
		window_.close();
	}
}

void Game::UpdateStatistics(sf::Time delta)
{
	statisticsUpdateTime_ += delta;
	statisticsNumFrames_ += 1;

	if (statisticsUpdateTime_ >= sf::seconds(1.0f))
	{
		statisticsText_.setString(std::to_string(statisticsNumFrames_) + " fps");
		statisticsUpdateTime_ -= sf::seconds(1.0f);
		statisticsNumFrames_ = 0;
	}
}
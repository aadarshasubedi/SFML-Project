#include "Application.h"
#include "State.h"
#include "StateTypes.h"
#include "GameState.h"
#include "TitleState.h"

Application::Application()
	: window_(sf::VideoMode(800, 400), "Saloon", sf::Style::Close)
	, textures_()
	, fonts_()
	, player_()
	, states_(State::Context(window_, textures_, fonts_, player_))
	, statisticsText_()
	, statisticsUpdateTime_()
	, statisticsNumFrames_(0)
{
	window_.setKeyRepeatEnabled(false);

	fonts_.Load(Fonts::Default, "assets/arial.ttf");
	textures_.Load(Textures::Title, "assets/gfx/title.png");

	statisticsText_.setFont(fonts_.get(Fonts::Default));
	statisticsText_.setPosition(5.0f, 5.0f);
	statisticsText_.setCharacterSize(10u);

	RegisterStates();
	states_.PushState(States::Title);
}

void Application::Run()
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

			if (states_.Empty())
			{
				window_.close();
			}
		}

		UpdateStatistics(dt);
		Render();
	}
}

void Application::ProcessInput()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		states_.HandleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
	}
}

void Application::Update(sf::Time delta)
{
	states_.Update(delta);
}

void Application::Render()
{
	window_.clear();

	states_.Draw();

	window_.setView(window_.getDefaultView());
	window_.draw(statisticsText_);

	window_.display();
}

void Application::RegisterStates()
{
	states_.RegisterState<TitleState>(States::Title);
	//states_.RegisterState<MenuState>(States::Menu);
	states_.RegisterState<GameState>(States::Game);
	//states_.RegisterState<PauseState>(States::Pause);
}

void Application::UpdateStatistics(sf::Time delta)
{
	statisticsUpdateTime_ += delta;
	statisticsNumFrames_ += 1;

	if (statisticsUpdateTime_ >= sf::seconds(1.0f))
	{
		statisticsText_.setString(std::to_string(statisticsNumFrames_) + " FPS");
		statisticsUpdateTime_ -= sf::seconds(1.0f);
		statisticsNumFrames_ = 0;
	}
}

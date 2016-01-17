#include "MenuState.h"
#include "GUI/Button.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateMachine & states, Context context)
	: State(states, context)
	, background_()
	, GUIcontainer_()
{
	background_.setTexture(context.textures_->get(Textures::Title));

	auto playButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	playButton->setPosition(300, 130);
	playButton->setText("PLAY");
	playButton->setTextColor(sf::Color::Black);
	playButton->setCallback([this]()
	{
		RequestPop();
		RequestPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	settingsButton->setPosition(playButton->getPosition() + sf::Vector2f(0.0f, 63.0f));
	settingsButton->setText("OPTIONS");
	settingsButton->setTextColor(sf::Color::Black);
	settingsButton->setCallback([this]()
	{
		RequestPush(States::Settings);
	});

	playButton->setTextColor(sf::Color::Black);
	auto quitButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	quitButton->setPosition(settingsButton->getPosition() + sf::Vector2f(0.0f, 63.0f));
	quitButton->setText("QUIT");
	quitButton->setTextColor(sf::Color::Black);
	quitButton->setCallback([this]()
	{
		RequestPop();
	});

	GUIcontainer_.Pack(playButton);
	GUIcontainer_.Pack(settingsButton);
	GUIcontainer_.Pack(quitButton);
}

void MenuState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;

	window.setView(window.getDefaultView());
	window.draw(background_);
	window.draw(GUIcontainer_);
}

bool MenuState::Update(sf::Time delta)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event & event)
{
	GUIcontainer_.HandleEvent(event);
	return false;
}

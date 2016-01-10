#include "PauseState.h"
#include "GUI/Button.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateMachine & states, Context context)
	: State(states, context)
	, background_()
	, GUIcontainer_()
{
	background_.setTexture(context.textures_->get(Textures::Title));

	auto resumeButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	resumeButton->setPosition(300, 130);
	resumeButton->setText("RESUME");
	resumeButton->setCallback([this]()
	{
		RequestPop();
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	settingsButton->setPosition(resumeButton->getPosition() + sf::Vector2f(0.0f, 63.0f));
	settingsButton->setText("OPTIONS");
	settingsButton->setCallback([this]()
	{
		RequestPush(States::Settings);
	});

	auto toMenuButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	toMenuButton->setPosition(settingsButton->getPosition() + sf::Vector2f(0.0f, 63.0f));
	toMenuButton->setText("RETURN TO MENU");
	toMenuButton->setCallback([this]()
	{
		RequestClear();
		RequestPush(States::Menu);
	});

	GUIcontainer_.Pack(resumeButton);
	GUIcontainer_.Pack(settingsButton);
	GUIcontainer_.Pack(toMenuButton);
}

void PauseState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;
	window.draw(background_);
	window.draw(GUIcontainer_);
}

bool PauseState::Update(sf::Time delta)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event & event)
{
	GUIcontainer_.HandleEvent(event);
	return false;
}
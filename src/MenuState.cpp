#include "MenuState.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateMachine & states, Context context)
	: State(states, context)
	, background_()
	, options_()
	, selectedOption_(0)
{
	background_.setTexture(context.textures_->get(Textures::Title));

	sf::Font & font = context.fonts_->get(Fonts::Default);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("PLAY");
	CenterOrigin(playOption);
	playOption.setPosition(context.window_->getView().getSize() / 2.0f);
	options_.push_back(playOption);

	sf::Text quitOption;
	quitOption.setFont(font);
	quitOption.setString("QUIT");
	CenterOrigin(quitOption);
	quitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.0f, 50.0f));
	options_.push_back(quitOption);

	UpdateText();
}

void MenuState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;

	window.setView(window.getDefaultView());
	window.draw(background_);
	for (auto & text : options_)
	{
		window.draw(text);
	}
}

bool MenuState::Update(sf::Time delta)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (selectedOption_ == Play)
		{
			RequestPop();
			RequestPush(States::Game);
		}
		else if (selectedOption_ == Quit)
		{
			RequestPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		selectedOption_ = (selectedOption_ > 0) ? selectedOption_ - 1 : options_.size() - 1;
		UpdateText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		selectedOption_ = (selectedOption_ < options_.size() - 1) ? selectedOption_ + 1 : 0;
		UpdateText();
	}

	return true;
}

void MenuState::UpdateText()
{
	if (options_.empty())
	{
		return;
	}

	for (auto & text : options_)
	{
		text.setStyle(sf::Text::Style::Regular);
	}

	options_[selectedOption_].setStyle(sf::Text::Style::Underlined);
}
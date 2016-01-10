#include "PauseState.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateMachine & states, Context context)
	: State(states, context)
	, background_()
	, options_()
	, selectedOption_(0)
{
	background_.setTexture(context.textures_->get(Textures::Title));

	sf::Font & font = context.fonts_->get(Fonts::Default);

	sf::Text resumeOption;
	resumeOption.setFont(font);
	resumeOption.setString("RESUME");
	CenterOrigin(resumeOption);
	resumeOption.setPosition(context.window_->getView().getSize() / 2.0f);
	options_.push_back(resumeOption);

	sf::Text quitOption;
	quitOption.setFont(font);
	quitOption.setString("RETURN TO MENU");
	CenterOrigin(quitOption);
	quitOption.setPosition(resumeOption.getPosition() + sf::Vector2f(0.0f, 50.0f));
	options_.push_back(quitOption);

	UpdateText();
}

void PauseState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;
	window.draw(background_);
	for (auto & text : options_)
	{
		window.draw(text);
	}
}

bool PauseState::Update(sf::Time delta)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (selectedOption_ == Resume)
		{
			RequestPop();
		}
		else if (selectedOption_ == Quit)
		{
			RequestClear();
			RequestPush(States::Menu);
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

	return false;
}

void PauseState::UpdateText()
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
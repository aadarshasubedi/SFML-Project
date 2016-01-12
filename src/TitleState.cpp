#include "TitleState.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateMachine & states, Context context)
	: State(states, context)
	, text_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	background_.setTexture(context.textures_->get(Textures::Title));
	text_.setFont(context.fonts_->get(Fonts::Default));
	text_.setString("Press any key to start");
	CenterOrigin(text_);
	text_.setPosition(context.window_->getView().getSize() / 2.0f);

}

void TitleState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;
	window.draw(background_);
	if (showText_)
	{
		window.draw(text_);
	}
}

bool TitleState::Update(sf::Time delta)
{
	textEffectTime_ += delta;

	if (textEffectTime_ >= sf::seconds(0.5f))
	{
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}
	return true;
}

bool TitleState::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Return)
		{
			RequestPop();
			RequestPush(States::Menu);
		}
	}
	return true;
}

#include "PauseState.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateMachine & states, Context context)
	: State(states, context)
	, background_()
	, text_()
{
	background_.setTexture(context.textures_->get(Textures::Title));
}

void PauseState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;
	window.draw(background_);
	window.draw(text_);
}

bool PauseState::Update(sf::Time delta)
{
	return true;
}

bool PauseState::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Return)
	{
		RequestPop();
	}
	return true;
}

#pragma once

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
	public:
					TitleState(StateMachine & states, Context context);
	virtual void	Draw();
	virtual bool	Update(sf::Time delta);
	virtual bool	HandleEvent(const sf::Event & event);

	private:
	sf::Sprite		background_;
	sf::Text		text_;
	bool			showText_;
	sf::Time		textEffectTime_;
};
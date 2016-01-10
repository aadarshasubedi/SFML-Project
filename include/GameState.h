#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameState : public State
{
	public:
	GameState(StateMachine & states, Context context);

	virtual void	Draw();
	virtual bool	Update(sf::Time delta);
	virtual bool	HandleEvent(const sf::Event & event);

	private:
	World			world_;
	Player &		player_;
};
#pragma once

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State
{
	public:
	MenuState(StateMachine & states, Context context);
	virtual void			Draw();
	virtual bool			Update(sf::Time delta);
	virtual bool			HandleEvent(const sf::Event & event);

	private:
	enum Options { Play, Quit };
	void					UpdateText();

	private:
	sf::Sprite				background_;
	std::vector<sf::Text>	options_;
	unsigned int			selectedOption_;
};
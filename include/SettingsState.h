#pragma once

#include "State.h"
#include "Player.h"
#include "GUI/Container.h"
#include "GUI/Button.h"
#include "GUI/Label.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class SettingsState : public State
{
	public:
					SettingsState(StateMachine & states, Context context);
	virtual void	Draw();
	virtual bool	Update(sf::Time delta);
	virtual bool	HandleEvent(const sf::Event & event);

	private:
	void			UpdateLabels();
	void			AddButtonLabel(Player::Action action, float y, const std::string & text, Context context);

	private:
	sf::Sprite											background_;
	GUI::Container										GUIcontainer_;
	std::array<GUI::Button::Ptr, Player::ActionCount>	bindingButtons_;
	std::array<GUI::Label::Ptr, Player::ActionCount>	bindingLabels_;
};
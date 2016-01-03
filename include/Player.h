#pragma once

#include "Command.h"

#include <SFML/Window/Event.hpp>

#include <map>

class CommandQueue;

class Player
{
	public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

	public:
											Player();
	void									HandleEvent(const sf::Event & event, CommandQueue & commands);
	void									HandleInput(CommandQueue & commands);

	void									AssignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key						getAssignedKey(Action action) const;

	private:
	void									InitBindings();
	void									InitActions();
	static bool								isRealTimeAction(Action action);

	private:
	std::map <sf::Keyboard::Key, Action>	keyBinding_;
	std::map<Action, Command>				actionBinding_;
};

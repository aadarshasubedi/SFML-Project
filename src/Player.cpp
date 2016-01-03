#include "Player.h"

#include "CommandQueue.h"
#include "Aircraft.h"

#include <string>
#include <algorithm>

struct AircraftMover
{
	AircraftMover(float vx, float vy): velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.Accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	InitBindings();
	InitActions();

	for (auto & pair : actionBinding_)
	{
		pair.second.category = Category::Player;
	}
}

void Player::HandleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = keyBinding_.find(event.key.code);
		if (found != keyBinding_.end() && !isRealTimeAction(found->second))
		{
			commands.Push(actionBinding_[found->second]);
		}
	}
}

void Player::HandleInput(CommandQueue & commands)
{
	for (auto pair : keyBinding_)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
		{
			commands.Push(actionBinding_[pair.second]);
		}
	}
}

void Player::AssignKey(Action action, sf::Keyboard::Key key)
{
	for (auto it = keyBinding_.begin(); it != keyBinding_.end(); ++it)
	{
		if (it->second == action)
		{
			keyBinding_.erase(it);
		}
	}

	keyBinding_[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : keyBinding_)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Unknown;
}

void Player::InitBindings()
{
	keyBinding_[sf::Keyboard::Left] = MoveLeft;
	keyBinding_[sf::Keyboard::Right] = MoveRight;
	keyBinding_[sf::Keyboard::Up] = MoveUp;
	keyBinding_[sf::Keyboard::Down] = MoveDown;
}

void Player::InitActions()
{
	const float playerSpeed = 200.f;

	actionBinding_[MoveLeft].action		= DerivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.0f));
	actionBinding_[MoveRight].action	= DerivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.0f));
	actionBinding_[MoveUp].action		= DerivedAction<Aircraft>(AircraftMover(0.0f, -playerSpeed));
	actionBinding_[MoveDown].action		= DerivedAction<Aircraft>(AircraftMover(0.0f, +playerSpeed));
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveUp:
		case MoveDown:
			return true;
		default:
			return false;
	}
}

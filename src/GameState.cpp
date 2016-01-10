#include "GameState.h"

GameState::GameState(StateMachine & states, Context context)
	: State(states, context)
	, world_(*context.window_)
	, player_(*context.player_)
{ }

void GameState::Draw()
{
	world_.Draw();
}

bool GameState::Update(sf::Time delta)
{
	world_.Update(delta);

	CommandQueue & commands = world_.getCommandQueue();
	player_.HandleInput(commands);
	
	return true;
}

bool GameState::HandleEvent(const sf::Event & event)
{
	CommandQueue & commands = world_.getCommandQueue();
	player_.HandleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Escape)
	{
		RequestPush(States::Pause);
	}

	return true;
}

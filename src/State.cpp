#include "State.h"
#include "StateMachine.h"

State::Context::Context(sf::RenderWindow & window, TextureManager & textures, FontManager & fonts, Player & player)
	: window_(&window)
	, textures_(&textures)
	, fonts_(&fonts)
	, player_(&player)
{ }

State::State(StateMachine & states, Context context)
	: states_(&states)
	, context_(context)
{ }

State::~State()
{
}

void State::RequestPush(States::ID stateID)
{
	states_->PushState(stateID);
}

void State::RequestPop()
{
	states_->PopState();
}

void State::RequestClear()
{
	states_->ClearState();
}

State::Context State::getContext() const
{
	return context_;
}

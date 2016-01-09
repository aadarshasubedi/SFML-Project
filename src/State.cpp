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
	states_->Push(stateID);
}

void State::RequestPop()
{
	states_->Pop();
}

void State::RequestClear()
{
	states_->Clear();
}

State::Context State::getContext() const
{
	return context_;
}

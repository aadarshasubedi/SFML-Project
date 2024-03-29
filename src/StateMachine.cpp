#include "StateMachine.h"

#include <cassert>

StateMachine::StateMachine(State::Context context)
	: states_()
	, pendingList_()
	, context_(context)
	, factories_()
{ }

void StateMachine::Update(sf::Time delta)
{
	// the states are updated from up to bottom : stack behavior
	for (auto it = states_.rbegin(); it != states_.rend(); ++it)
	{
		if (!(*it)->Update(delta))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateMachine::Draw()
{
	for (auto & state : states_)
	{
		state->Draw();
	}
}

void StateMachine::HandleEvent(const sf::Event & event)
{
	for (auto it = states_.rbegin(); it != states_.rend(); ++it)
	{
		if (!(*it)->HandleEvent(event))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateMachine::PushState(States::ID stateID)
{
	pendingList_.push_back(PendingChange(Action::Push, stateID));
}

void StateMachine::PopState()
{
	pendingList_.push_back(PendingChange(Action::Pop));
}

void StateMachine::ClearState()
{
	pendingList_.push_back(PendingChange(Action::Clear));
}

bool StateMachine::Empty() const
{
	return states_.empty();
}

State::Ptr StateMachine::CreateState(States::ID stateID)
{
	auto found = factories_.find(stateID);
	assert(found != factories_.end());
	return found->second();
}

void StateMachine::ApplyPendingChanges()
{
	for (auto change : pendingList_)
	{
		switch (change.action_)
		{
			case Action::Push:
				states_.push_back(CreateState(change.stateID_));
				break;
			case Action::Pop:
				states_.pop_back();
				break;
			case Action::Clear:
				states_.clear();
				break;
		}
	}

	pendingList_.clear();
}

StateMachine::PendingChange::PendingChange(Action action, States::ID stateID)
	: action_(action)
	, stateID_(stateID)
{ }

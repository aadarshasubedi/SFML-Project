#pragma once

#include "State.h"
#include "StateTypes.h"
#include "ResourceTypes.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateMachine : private sf::NonCopyable
{
	public:
	enum Action { Push, Pop, Clear };

	public:
	explicit	StateMachine(State::Context context);

	void		Update(sf::Time delta);
	void		Draw();
	void		HandleEvent(const sf::Event & event);

	void		Push(States::ID stateID);
	void		Pop();
	void		Clear();

	bool		Empty() const;

	template <typename T>
	void		RegisterState(States::ID stateID);

	private:
	State::Ptr	CreateState(States::ID stateID);
	void		ApplyPendingChanges();

	struct PendingChange
	{
		explicit	PendingChange(Action action, States::ID stateID = States::None);
		Action		action_;
		States::ID	stateID_;
	};

	private:
	std::vector<State::Ptr>		states_;
	std::vector<PendingChange>	pendingList_;
	State::Context				context_;
	std::map<States::ID, std::function<State::Ptr()>> factories_;
};

template <typename T>
void StateMachine::RegisterState(States::ID stateID)
{
	factories_[stateID] = [this]()
	{
		return State::Ptr(new T(*this, context_));
	}
}
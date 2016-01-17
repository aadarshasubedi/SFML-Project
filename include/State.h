#pragma once

#include "ResourceTypes.h"
#include "StateTypes.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
}

class StateMachine;
class Player;

class State
{
	public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow & window, TextureManager & textures, FontManager & fonts, Player & player);

		sf::RenderWindow *	window_;
		TextureManager *	textures_;
		FontManager *		fonts_;
		Player *			player_;
	};

	public:
					State(StateMachine & states, Context context);
	virtual			~State();

	virtual void	Draw() = 0;
	virtual bool	Update(sf::Time delta) = 0;
	virtual bool	HandleEvent(const sf::Event & event) = 0;
	virtual bool	isActive() const;

	protected:
	void			RequestPush(States::ID stateID);
	void			RequestPop();
	void			RequestClear();
	Context			getContext() const;

	private:
	StateMachine *	states_;
	Context			context_;
	bool			active_;

};

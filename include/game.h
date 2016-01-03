#pragma once

#include "World.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game : private sf::NonCopyable
{
	public:
						Game();

	void				Run(int fps);

	private:
	void				ProcessEvents();
	void				Update(sf::Time delta);
	void				Render();
	void				HandleInput(sf::Keyboard::Key key, bool isPressed);

	private:
	sf::RenderWindow	window_;
	World				world_;
};
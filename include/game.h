#pragma once

#include "Player.h"
#include "World.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Game : private sf::NonCopyable
{
	public:
						Game();

	void				Run();

	private:
	void				ProcessInput();
	void				Update(sf::Time delta);
	void				Render();
	void				HandleInput(sf::Keyboard::Key key, bool isPressed);

	private:
	sf::RenderWindow	window_;
	World				world_;
	Player				player_;

	private: // For displaying statistics
	void					UpdateStatistics(sf::Time delta);
	sf::Font				font_;
	sf::Text				statisticsText_;
	sf::Time				statisticsUpdateTime_;
	std::size_t				statisticsNumFrames_;
};